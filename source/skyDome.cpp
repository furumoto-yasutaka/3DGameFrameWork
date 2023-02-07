/*******************************************************************************
*
*	�^�C�g���F	�X�J�C�h�[���ÓI�N���X	[ skyDome.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "skyDome.h"
#include "renderer.h"
#include "modelContainer.h"
#include "manager.h"
#include "camera.h"
#include "gameObject.h"

string				SkyDome::m_ModelName = "SkyDome";
Model*				SkyDome::m_Model = NULL;
ID3D11VertexShader* SkyDome::m_VertexShader = NULL;
ID3D11PixelShader*	SkyDome::m_PixelShader = NULL;
ID3D11InputLayout*	SkyDome::m_VertexLayout = NULL;
float				SkyDome::m_Size;

void SkyDome::Init()
{
	// ���f���擾
	m_Model = ModelContainer::GetModel_InName(m_ModelName);

	// �V�F�[�_�[�ݒ�
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	// �h�[���̃T�C�Y�ݒ�(�ő�`�拗�� * 0.9)
	m_Size = 1000.0f * 0.9f;
}

void SkyDome::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SkyDome::Draw()
{
	// ���f�������[�h����Ă��邩�m�F
	if (!m_Model->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("���f�����ǂݍ��܂�Ă��܂���\n�^�O�����Ă��Ȃ��\��������܂�\n") + m_ModelName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("skyDome:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// ���ݗL���ɂȂ��Ă���J�������擾
	Camera* camera = Manager::GetScene()->GetActiveCamera();
	if (!camera)
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("�J�������擾�ł��܂���ł���\n�J�������V�[���ɑ��݂��Ă��Ȃ��\��������܂�\n");
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("skyDome:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//------------------------
	// ���[���h�}�g���N�X�ݒ�
	//------------------------
	D3DXVECTOR3 s = D3DXVECTOR3(m_Size, m_Size, m_Size);
	D3DXVECTOR3 p = camera->GetAttachObject()->m_LocalPosition;	// �J�����ɒǏ]������
	p.y = -3.0f;

	D3DXMATRIX world, scale, trans;
	D3DXMatrixScaling(&scale, s.x, s.y, s.z);
	D3DXMatrixTranslation(&trans, p.x, p.y, p.z);
	world = scale * trans;

	Renderer::SetWorldMatrix(&world);

	// �`��
	m_Model->Draw();
}
