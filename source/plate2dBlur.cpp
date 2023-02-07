/*******************************************************************************
*
*	�^�C�g���F	�e�N�X�`���u���[�R���|�[�l���g	[ plate2dBlur.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "plate2dBlur.h"
#include "gameObject.h"
#include "plate2dRenderer.h"
#include "texture.h"

void TextureBulr2D::Init(Plate2DRenderer* Plate2D, unsigned int BulrLayer, unsigned int BulrInterval, unsigned int InterpolationBlur)
{
	m_Plate2DRenderer = Plate2D;

	// �s���Ȓl�̏ꍇ�͕␳����
	if (BulrLayer <= 0) { m_BulrLayer = 1; }
	else { m_BulrLayer = BulrLayer; }

	// �s���Ȓl�̏ꍇ�͕␳����
	if (BulrInterval <= 0) { m_BulrInterval = 1; }
	else { m_BulrInterval = BulrInterval; }

	m_BulrAlphaDecayRate = 1.0f / (m_BulrLayer * InterpolationBlur);
	m_InterpolationBlur = InterpolationBlur;

	//-------------------
	// �o�b�t�@�ݒ�
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �o�b�t�@����
	Renderer::GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);

	// �V�F�[�_�[�ݒ�
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
		// �u���[���ő吔�̏ꍇ�Ō�ɐ��������u���[���폜����
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

		// �u���[��ǉ�����
		m_BulrPosition.push_front({ m_AttachObject->GetWorldPosition().x, m_AttachObject->GetWorldPosition().y });
		m_BulrRotationZ.push_front(Math::QuaternionToEulerAngle(m_AttachObject->GetWorldRotation()).z);

		// �␳�u���[���ǉ�����
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
		// ���_��񏑂�����
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		float alpha = m_BulrAlphaDecayRate * i;	// �����x
		GetVertex((VERTEX_3D*)msr.pData, *posItr, alpha, *rotItr);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		// ���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		// �V�F�[�_�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		// �}�g���N�X�ݒ�
		Renderer::SetWorldViewProjection2D();

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		// �e�N�X�`���ݒ�
		ID3D11ShaderResourceView* resource = m_Plate2DRenderer->GetTexture()->GetResource();
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &resource);

		// �v���~�e�B�u�g�|���W�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

/*******************************************************************************
*	���_�����擾
*******************************************************************************/
void TextureBulr2D::GetVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Pos, float Alpha, float Rot)
{
	D3DXVECTOR3 worldScale = m_AttachObject->GetWorldScale();
	D3DXVECTOR2 size = m_Plate2DRenderer->GetSize();
	D3DXVECTOR2 halfScale;

	// �s�{�b�g�ʒu�ɉ������ݒ�Ő���
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
*	���_���𐶐�
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

	// ��]�𔽉f�������_���W�̏���ۑ�
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
