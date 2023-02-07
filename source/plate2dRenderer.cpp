/*******************************************************************************
*
*	�^�C�g���F	2D�|���S���`��R���|�[�l���g	[ plate2dRenderer.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
	// ������
	m_TextureName = TextureName;
	m_Size = Size;
	m_RenderMode = Mode;
	m_AnchorPosition = AnchorPos;
	m_TexCoordBegin = D3DXVECTOR2(0.0f, 0.0f);
	m_TexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Animation = NULL;

	// �e�N�X�`���擾
	m_Texture = TextureContainer::GetTexture_InName(m_TextureName);
	m_TexCoordDistance.x = 1.0f / m_Texture->GetWidthDiv();
	m_TexCoordDistance.y = 1.0f / m_Texture->GetHeightDiv();

	//-------------------
	// �o�b�t�@�ݒ�
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (m_RenderMode == Renderer::TextureRenderMode::Static)
	{// �ÓI�ݒ�
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0;
	}
	else
	{// ���I�ݒ�
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	VERTEX_3D vertex[4];
	GetVertex(vertex);
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	// �o�b�t�@����
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// �V�F�[�_�[�ݒ�
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
	// �e�N�X�`�������[�h����Ă��邩�m�F
	if (!m_Texture->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("�e�N�X�`�����ǂݍ��܂�Ă��܂���\n�^�O�����Ă��Ȃ��\��������܂�\n") + m_TextureName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("plate2DRenderer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// �e�N�X�`�����X�V
	D3DXVECTOR3 p = m_AttachObject->m_LocalPosition;
	if (m_RenderMode == Renderer::TextureRenderMode::Dynamic)
	{
		// ���_��񏑂�����
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);
		GetVertex((VERTEX_3D*)msr.pData);

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

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
	ID3D11ShaderResourceView* resource = m_Texture->GetResource();
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &resource);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}

/*******************************************************************************
*	�e�N�X�`���A�j���[�V�����Ɛڑ�
*******************************************************************************/
void Plate2DRenderer::Connect(TextureAnimation* Animation,
	D3DXVECTOR2*& TexCoordBegin, D3DXVECTOR2*& TexCoordDistance,
	int& WidthDiv, int& HeightDiv)
{
	// �R���|�[�l���g��o�^
	m_Animation = Animation;

	// �ϐ��̒l�����L
	TexCoordBegin = &m_TexCoordBegin;
	TexCoordDistance = &m_TexCoordDistance;
	WidthDiv = m_Texture->GetWidthDiv();
	HeightDiv = m_Texture->GetHeightDiv();

	// �`��ݒ肪�ÓI�ɂȂ��Ă���ꍇ�͓��I�ɕύX����
	if (m_RenderMode == Renderer::TextureRenderMode::Static)
	{
		m_RenderMode = Renderer::TextureRenderMode::Dynamic;

		//-------------------
		// �o�b�t�@�ݒ�
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
*	�e�N�X�`���A�j���[�V�����Ƃ̐ڑ�������
*******************************************************************************/
void Plate2DRenderer::DisConnect()
{
	if (!m_Animation) { return; }
	m_Animation->SetDestroy();
	m_Animation = nullptr;
}

/*******************************************************************************
*	���g�̍폜��\��
*******************************************************************************/
void Plate2DRenderer::SetDestroy()
{
	if (m_Animation) { m_Animation->SetDestroy(); }
	m_Destroy = true;
}

/*******************************************************************************
*	�e�N�X�`���ύX
*******************************************************************************/
void Plate2DRenderer::SetTexture(string Name)
{
	m_TextureName = Name;

	// �e�N�X�`�����W���Čv�Z
	m_Texture = TextureContainer::GetTexture_InName(m_TextureName);
	m_TexCoordDistance.x = 1.0f / m_Texture->GetWidthDiv();
	m_TexCoordDistance.y = 1.0f / m_Texture->GetHeightDiv();
}

/*******************************************************************************
*	���_�����擾
*******************************************************************************/
void Plate2DRenderer::GetVertex(VERTEX_3D* Vertex)
{
	D3DXVECTOR3 s = m_AttachObject->GetWorldScale();
	D3DXVECTOR2 halfScale;

	// �s�{�b�g�ʒu�ɉ������ݒ�Ő���
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
*	���_���𐶐�
*******************************************************************************/
void Plate2DRenderer::CreateVertex(VERTEX_3D* Vertex, D3DXVECTOR2 Offset)
{
	D3DXVECTOR2 p = { m_AttachObject->GetLocalPositionOrigin().x + Offset.x, m_AttachObject->GetLocalPositionOrigin().y + Offset.y };
	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR2 rotOffsetPlus;
	D3DXVECTOR2 rotOffsetMinus;

	// �e�̉�]�𔽉f
	{
		D3DXVECTOR2 localPos = { m_AttachObject->m_LocalPosition.x, m_AttachObject->m_LocalPosition.y };
		float baseAngle = atan2f(localPos.x, localPos.y);
		float len = D3DXVec2Length(&localPos);
		float rot = Math::QuaternionToEulerAngle(m_AttachObject->GetLocalRotationOrigin()).z;
		p += { sinf(baseAngle + rot) * len, cosf(baseAngle + rot) * len };
	}
	// ���g�̉�]�𔽉f
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
