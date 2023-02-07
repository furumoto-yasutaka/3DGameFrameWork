/*******************************************************************************
*
*	タイトル：	3D板ポリゴン描画コンポーネント	[ plate3dRenderer.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "plate3dRenderer.h"
#include "textureContainer.h"
#include "gameobject.h"
#include "textureAnimation.h"
#include "camera.h"

void Plate3DRenderer::Init(const char* TextureName, D3DXVECTOR2 Size,
	Renderer::TextureRenderMode Mode, AnchorPosition AnchorPos,
	bool IsBillBoard, bool IsAlphaToCoverage)
{
	// 初期化
	m_TextureName = TextureName;
	m_Size = Size;
	m_RenderMode = Mode;
	m_AnchorPosition = AnchorPos;
	m_IsBillBoard = IsBillBoard;
	m_IsAlphaToCoverage = IsAlphaToCoverage;
	m_TexCoordBegin = D3DXVECTOR2(0.0f, 0.0f);
	m_TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Animation = NULL;

	// テクスチャ取得
	m_Texture = TextureContainer::GetTexture_InName(m_TextureName);
	m_TexCoordDistance.x = 1.0f / m_Texture->GetWidthDiv();
	m_TexCoordDistance.y = 1.0f / m_Texture->GetHeightDiv();

	//-------------------
	// バッファ設定
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (m_RenderMode == Renderer::TextureRenderMode::Static)
	{// 静的設定
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
	}
	else
	{// 動的設定
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	VERTEX_3D vertex[4];
	GetVertex(vertex);
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	// バッファ生成
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}

void Plate3DRenderer::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Plate3DRenderer::Update()
{

}

void Plate3DRenderer::Draw()
{
	// テクスチャがロードされているか確認
	if (!m_Texture->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("テクスチャが読み込まれていません\nタグがついていない可能性があります\n") + m_TextureName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("plate3DRenderer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// テクスチャ情報更新
	if (m_RenderMode == Renderer::TextureRenderMode::Dynamic)
	{
		// 頂点情報書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);
		GetVertex((VERTEX_3D*)msr.pData);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	// アルファトゥカバレッジ設定
	Renderer::SetAlphaToCaverage(m_IsAlphaToCoverage);

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	if (m_IsBillBoard)
	{// ビルボード有効
		Camera* cam = Manager::GetScene()->GetActiveCamera();
		D3DXMATRIX view = cam->GetViewMatrix();
		D3DXMATRIX invView;
		D3DXMatrixInverse(&invView, NULL, &view);
		invView._41 = 0.0f;
		invView._42 = 0.0f;
		invView._43 = 0.0f;

		D3DXMATRIX world, scale, trans;
		D3DXVECTOR3 scl = m_AttachObject->GetWorldScale();
		D3DXVECTOR3 pos = m_AttachObject->GetWorldPosition();
		D3DXMatrixScaling(&scale, scl.x, scl.y, scl.z);
		D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);

		world = scale * invView * trans;
		Renderer::SetWorldMatrix(&world);
	}
	else
	{// ビルボード無効
		D3DXMATRIX m = m_AttachObject->GetWorldMatrix();
		Renderer::SetWorldMatrix(&m);
	}

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// テクスチャ設定
	ID3D11ShaderResourceView* resource = m_Texture->GetResource();
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &resource);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}

/*******************************************************************************
*	テクスチャアニメーションと接続
*******************************************************************************/
void Plate3DRenderer::Connect(TextureAnimation* Animation,
	D3DXVECTOR2*& TexCoordBegin, D3DXVECTOR2*& TexCoordDistance,
	int& WidthDiv, int& HeightDiv)
{
	// コンポーネントを登録
	m_Animation = Animation;

	// 変数の値を共有
	TexCoordBegin = &m_TexCoordBegin;
	TexCoordDistance = &m_TexCoordDistance;
	WidthDiv = m_Texture->GetWidthDiv();
	HeightDiv = m_Texture->GetHeightDiv();

	// 描画設定が静的になっている場合は動的に変更する
	if (m_RenderMode == Renderer::TextureRenderMode::Static)
	{
		m_RenderMode = Renderer::TextureRenderMode::Dynamic;

		//------------------------
		// バッファ設定
		//------------------------
		D3D11_BUFFER_DESC bd;
		m_VertexBuffer->GetDesc(&bd);
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		VERTEX_3D vertex[4];
		GetVertex(vertex);
		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}
}

/*******************************************************************************
*	テクスチャアニメーションとの接続を解除
*******************************************************************************/
void Plate3DRenderer::DisConnect()
{
	if (!m_Animation) { return; }
	m_Animation->SetDestroy();
	m_Animation = nullptr;
}

/*******************************************************************************
*	自身の削除を予約
*******************************************************************************/
void Plate3DRenderer::SetDestroy()
{
	if (m_Animation) { m_Animation->SetDestroy(); }
	m_Destroy = true;
}

/*******************************************************************************
*	テクスチャ変更
*******************************************************************************/
void Plate3DRenderer::SetTexture(string Name)
{
	m_TextureName = Name;

	// テクスチャ座標を再計算
	m_Texture = TextureContainer::GetTexture_InName(m_TextureName);
	m_TexCoordDistance.x = 1.0f / m_Texture->GetWidthDiv();
	m_TexCoordDistance.y = 1.0f / m_Texture->GetHeightDiv();
}

/*******************************************************************************
*	頂点情報を取得
*******************************************************************************/
void Plate3DRenderer::GetVertex(VERTEX_3D* Vertex)
{
	D3DXVECTOR3 s = m_AttachObject->GetWorldScale();
	D3DXVECTOR2 halfScale;

	// ピボット位置に応じた設定で生成
	switch (m_AnchorPosition)
	{
	case AnchorPosition::Left_Top:
		CreateVertex(Vertex, D3DXVECTOR2(0.0f, 0.0f));
		break;
	case AnchorPosition::Center_Middle:
		halfScale = m_Size * 0.5f;
		CreateVertex(Vertex, -halfScale);
		break;
	default: return;
	}
}

/*******************************************************************************
*	頂点情報を生成
*******************************************************************************/
void Plate3DRenderer::CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Offset)
{
	D3DXVECTOR3 n;
	// 法線設定
	if (m_IsBillBoard)
	{
		// ビルボードが有効の場合はカメラの方向を向くようにする
		n = -Manager::GetScene()->GetActiveCamera()->GetAttachObject()->GetForward();
	}
	else { n = m_AttachObject->GetForward(); }

	Vertex[0].Position = D3DXVECTOR3(Offset.x, Offset.y + m_Size.y, 0.0f);
	Vertex[0].Normal = n;
	Vertex[0].Diffuse = m_TexColor;
	Vertex[0].TexCoord = m_TexCoordBegin;

	Vertex[1].Position = D3DXVECTOR3(Offset.x + m_Size.x, Offset.y + m_Size.y, 0.0f);
	Vertex[1].Normal = n;
	Vertex[1].Diffuse = m_TexColor;
	Vertex[1].TexCoord = D3DXVECTOR2(m_TexCoordBegin.x + m_TexCoordDistance.x,
		m_TexCoordBegin.y);

	Vertex[2].Position = D3DXVECTOR3(Offset.x, Offset.y, 0.0f);
	Vertex[2].Normal = n;
	Vertex[2].Diffuse = m_TexColor;
	Vertex[2].TexCoord = D3DXVECTOR2(m_TexCoordBegin.x,
		m_TexCoordBegin.y + m_TexCoordDistance.y);

	Vertex[3].Position = D3DXVECTOR3(Offset.x + m_Size.x, Offset.y, 0.0f);
	Vertex[3].Normal = n;
	Vertex[3].Diffuse = m_TexColor;
	Vertex[3].TexCoord = m_TexCoordBegin + m_TexCoordDistance;
}
