/*******************************************************************************
*
*	タイトル：	2D板ポリゴン描画コンポーネント	[ plate2dRenderer.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "Plate2dRenderer.h"
#include "textureContainer.h"
#include "gameObject.h"
#include "textureAnimation.h"

void Plate2DRenderer::Init(const char* TextureName,
	D3DXVECTOR2 Size,
	Renderer::TextureRenderMode Mode,
	AnchorPosition AnchorPos)
{
	// 初期化
	m_TextureName = TextureName;
	m_Size = Size;
	m_RenderMode = Mode;
	m_AnchorPosition = AnchorPos;
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
void Plate2DRenderer::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}
void Plate2DRenderer::Update()
{

}
void Plate2DRenderer::Draw()
{
	// テクスチャがロードされているか確認
	if (!m_Texture->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("テクスチャが読み込まれていません\nタグがついていない可能性があります\n") + m_TextureName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("plate2DRenderer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// テクスチャ情報更新
	D3DXVECTOR3 p = m_AttachObject->m_LocalPosition;
	if (m_RenderMode == Renderer::TextureRenderMode::Dynamic)
	{
		// 頂点情報書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);
		GetVertex((VERTEX_3D*)msr.pData);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

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
void Plate2DRenderer::Connect(TextureAnimation* Animation,
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

		//-------------------
		// バッファ設定
		//-------------------
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
void Plate2DRenderer::DisConnect()
{
	if (!m_Animation) { return; }
	m_Animation->SetDestroy();
	m_Animation = nullptr;
}

/*******************************************************************************
*	自身の削除を予約
*******************************************************************************/
void Plate2DRenderer::SetDestroy()
{
	if (m_Animation) { m_Animation->SetDestroy(); }
	m_Destroy = true;
}

/*******************************************************************************
*	テクスチャ変更
*******************************************************************************/
void Plate2DRenderer::SetTexture(string Name)
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
void Plate2DRenderer::GetVertex(VERTEX_3D* Vertex)
{
	D3DXVECTOR3 s = m_AttachObject->GetWorldScale();
	D3DXVECTOR2 halfScale;

	// ピボット位置に応じた設定で生成
	switch (m_AnchorPosition)
	{
	case AnchorPosition::Left_Top:
		halfScale = { m_Size.x * s.x * 0.5f, m_Size.y * s.y * 0.5f };
		CreateVertex(Vertex, halfScale);
		break;
	case AnchorPosition::Center_Middle:
		CreateVertex(Vertex, D3DXVECTOR2(0.0f, 0.0f));
		break;
	default: return;
	}
}

/*******************************************************************************
*	頂点情報を生成
*******************************************************************************/
void Plate2DRenderer::CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Offset)
{
	D3DXVECTOR2 p = { m_AttachObject->GetLocalPositionOrigin().x + Offset.x, m_AttachObject->GetLocalPositionOrigin().y + Offset.y };
	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 rotOffsetPlus;
	D3DXVECTOR2 rotOffsetMinus;

	// 親の回転を反映
	{
		D3DXVECTOR2 localPos = { m_AttachObject->m_LocalPosition.x, m_AttachObject->m_LocalPosition.y };
		float baseAngle = atan2f(localPos.x, localPos.y);
		float len = D3DXVec2Length(&localPos);
		float rot = Math::QuaternionToEulerAngle(m_AttachObject->GetLocalRotationOrigin()).z;
		p += { sinf(baseAngle + rot) * len, cosf(baseAngle + rot) * len };
	}
	// 自身の回転を反映
	{
		D3DXVECTOR3 s = m_AttachObject->GetWorldScale();
		D3DXVECTOR2 halfScale = { m_Size.x * s.x * 0.5f, m_Size.y * s.y * 0.5f };
		float baseAngle = atan2f(halfScale.x, halfScale.y);
		float len = D3DXVec2Length(&halfScale);
		float rot = Math::QuaternionToEulerAngle(m_AttachObject->m_LocalRotation).z;
		rotOffsetPlus = { sinf(baseAngle + rot) * len, cosf(baseAngle + rot) * len };
		rotOffsetMinus = { sinf(baseAngle - rot) * len, cosf(baseAngle - rot) * len };
	}

	Vertex[0].Position = D3DXVECTOR3(p.x - rotOffsetMinus.x, p.y - rotOffsetMinus.y, 0.0f);
	Vertex[0].Normal = n;
	Vertex[0].Diffuse = m_TexColor;
	Vertex[0].TexCoord = D3DXVECTOR2(m_TexCoordBegin.x,
		m_TexCoordBegin.y);

	Vertex[1].Position = D3DXVECTOR3(p.x + rotOffsetPlus.x, p.y - rotOffsetPlus.y, 0.0f);
	Vertex[1].Normal = n;
	Vertex[1].Diffuse = m_TexColor;
	Vertex[1].TexCoord = D3DXVECTOR2(m_TexCoordBegin.x + m_TexCoordDistance.x,
		m_TexCoordBegin.y);

	Vertex[2].Position = D3DXVECTOR3(p.x - rotOffsetPlus.x, p.y + rotOffsetPlus.y, 0.0f);
	Vertex[2].Normal = n;
	Vertex[2].Diffuse = m_TexColor;
	Vertex[2].TexCoord = D3DXVECTOR2(m_TexCoordBegin.x,
		m_TexCoordBegin.y + m_TexCoordDistance.y);

	Vertex[3].Position = D3DXVECTOR3(p.x + rotOffsetMinus.x, p.y + rotOffsetMinus.y, 0.0f);
	Vertex[3].Normal = n;
	Vertex[3].Diffuse = m_TexColor;
	Vertex[3].TexCoord = D3DXVECTOR2(m_TexCoordBegin.x + m_TexCoordDistance.x,
		m_TexCoordBegin.y + m_TexCoordDistance.y);
}
