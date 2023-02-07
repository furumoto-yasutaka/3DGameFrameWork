/*******************************************************************************
*
*	タイトル：	テクスチャブラーコンポーネント	[ plate2dBlur.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "plate2dBlur.h"
#include "gameObject.h"
#include "plate2dRenderer.h"
#include "texture.h"

void TextureBulr2D::Init(Plate2DRenderer* Plate2D, unsigned int BulrLayer, unsigned int BulrInterval, unsigned int InterpolationBlur)
{
	m_Plate2DRenderer = Plate2D;

	// 不正な値の場合は補正する
	if (BulrLayer <= 0) { m_BulrLayer = 1; }
	else { m_BulrLayer = BulrLayer; }

	// 不正な値の場合は補正する
	if (BulrInterval <= 0) { m_BulrInterval = 1; }
	else { m_BulrInterval = BulrInterval; }

	m_BulrAlphaDecayRate = 1.0f / (m_BulrLayer * InterpolationBlur);
	m_InterpolationBlur = InterpolationBlur;

	//-------------------
	// バッファ設定
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// バッファ生成
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}

void TextureBulr2D::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TextureBulr2D::Update()
{
	if (m_FrameCount >= m_BulrInterval)
	{
		// ブラーが最大数の場合最後に生成したブラーを削除する
		if ((signed)m_BulrPosition.size() == m_BulrLayer)
		{
			m_BulrPosition.pop_back();
			m_BulrRotationZ.pop_back();
			
			for (int i = 0; i < m_InterpolationBlur; i++)
			{
				m_BulrPosition.pop_back();
				m_BulrRotationZ.pop_back();
			}
		}

		// ブラーを追加する
		m_BulrPosition.push_front({ m_AttachObject->GetWorldPosition().x, m_AttachObject->GetWorldPosition().y });
		m_BulrRotationZ.push_front(Math::QuaternionToEulerAngle(m_AttachObject->GetWorldRotation()).z);

		// 補正ブラーも追加する
		auto posItr = m_BulrPosition.rbegin();
		auto posItrNext = posItr; posItrNext++;
		D3DXVECTOR2 divPosRate = *posItrNext - *posItr;
		divPosRate /= (float)(m_InterpolationBlur + 1);

		auto rotItr = m_BulrRotationZ.rbegin();
		auto rotItrNext = rotItr; rotItrNext++;
		float divRotRate = *rotItrNext - *rotItr;
		divRotRate /= (float)(m_InterpolationBlur + 1);

		for (int i = 0; i < m_InterpolationBlur; i++)
		{
			m_BulrPosition.push_front(*posItr + divPosRate * (float)i);
			m_BulrRotationZ.push_front(*rotItr + divRotRate * (float)i);
		}
	}

	m_FrameCount++;
}

void TextureBulr2D::Draw()
{
	auto posItr = m_BulrPosition.rbegin();
	auto rotItr = m_BulrRotationZ.rbegin();
	int i = 0;
	for (; posItr != m_BulrPosition.rend() && rotItr != m_BulrRotationZ.rend(); posItr++, rotItr++, i++)
	{
		// 頂点情報書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		float alpha = m_BulrAlphaDecayRate * i;	// 透明度
		GetVertex((VERTEX_3D*)msr.pData, *posItr, alpha, *rotItr);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

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
		ID3D11ShaderResourceView* resource = m_Plate2DRenderer->GetTexture()->GetResource();
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &resource);

		// プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

/*******************************************************************************
*	頂点情報を取得
*******************************************************************************/
void TextureBulr2D::GetVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, float Alpha, float Rot)
{
	D3DXVECTOR3 worldScale = m_AttachObject->GetWorldScale();
	D3DXVECTOR2 size = m_Plate2DRenderer->GetSize();
	D3DXVECTOR2 halfScale;

	// ピボット位置に応じた設定で生成
	switch (m_Plate2DRenderer->GetAnchorPosition())
	{
	case Plate2DRenderer::AnchorPosition::Left_Top:
		halfScale = { size.x * worldScale.x * 0.5f, size.y * worldScale.y * 0.5f };
		CreateVertex(Vertex, Pos, halfScale, Alpha, Rot);
		break;
	case Plate2DRenderer::AnchorPosition::Center_Middle:
		CreateVertex(Vertex, Pos, D3DXVECTOR2(0.0f, 0.0f), Alpha, Rot);
		break;
	default: return;
	}
}

/*******************************************************************************
*	頂点情報を生成
*******************************************************************************/
void TextureBulr2D::CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, D3DXVECTOR2 Offset, float Alpha, float Rot)
{
	D3DXVECTOR2 p = Pos - Offset;
	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR c = D3DXCOLOR(1.0f, 1.0f, 1.0f, Alpha);
	D3DXVECTOR2 begin = m_Plate2DRenderer->GetTexCoordBegin();
	D3DXVECTOR2 distance = m_Plate2DRenderer->GetTexCoordDistance();
	D3DXVECTOR2 rotOffsetPlus;
	D3DXVECTOR2 rotOffsetMinus;

	// 回転を反映した頂点座標の情報を保存
	{
		D3DXVECTOR2 size = m_Plate2DRenderer->GetSize();
		D3DXVECTOR3 worldScale = m_AttachObject->GetWorldScale();
		D3DXVECTOR2 halfScale = { size.x * worldScale.x * 0.5f, size.y * worldScale.y * 0.5f };
		float baseAngle = atan2f(halfScale.x, halfScale.y);
		float len = D3DXVec2Length(&halfScale);
		float rot = Math::QuaternionToEulerAngle(m_AttachObject->GetWorldRotation()).z;
		rotOffsetPlus = { sinf(baseAngle + rot) * len, cosf(baseAngle + rot) * len };
		rotOffsetMinus = { sinf(baseAngle - rot) * len, cosf(baseAngle - rot) * len };
	}

	Vertex[0].Position = D3DXVECTOR3(p.x - rotOffsetMinus.x, p.y - rotOffsetMinus.y, 0.0f);
	Vertex[0].Normal = n;
	Vertex[0].Diffuse = c;
	Vertex[0].TexCoord = begin;

	Vertex[1].Position = D3DXVECTOR3(p.x + rotOffsetPlus.x, p.y - rotOffsetPlus.y, 0.0f);
	Vertex[1].Normal = n;
	Vertex[1].Diffuse = c;
	Vertex[1].TexCoord = D3DXVECTOR2(begin.x + distance.x, begin.y);

	Vertex[2].Position = D3DXVECTOR3(p.x - rotOffsetPlus.x, p.y + rotOffsetPlus.y, 0.0f);
	Vertex[2].Normal = n;
	Vertex[2].Diffuse = c;
	Vertex[2].TexCoord = D3DXVECTOR2(begin.x, begin.y + distance.y);

	Vertex[3].Position = D3DXVECTOR3(p.x + rotOffsetMinus.x, p.y + rotOffsetMinus.y, 0.0f);
	Vertex[3].Normal = n;
	Vertex[3].Diffuse = c;
	Vertex[3].TexCoord = begin + distance;
}
