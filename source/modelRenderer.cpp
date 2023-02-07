/*******************************************************************************
*
*	�^�C�g���F	���f���`��R���|�[�l���g	[ modelRenderer.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "modelRenderer.h"
#include "renderer.h"
#include "modelContainer.h"
#include "gameObject.h"
#include "input.h"

void ModelRenderer::Init(const char* ModelName, string VertexShaderName, string PixelShaderName)
{
	m_ModelName = ModelName;
	m_VertexShaderName = VertexShaderName + ".cso";
	m_PixelShaderName = PixelShaderName + ".cso";

	// ���f���擾
	m_Model = ModelContainer::GetModel_InName(m_ModelName);

	// �V�F�[�_�[�ݒ�
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, m_VertexShaderName.c_str());
	Renderer::CreatePixelShader(&m_PixelShader, m_PixelShaderName.c_str());
}

void ModelRenderer::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ModelRenderer::Update()
{

}

void ModelRenderer::Draw()
{
	// ���f�������[�h����Ă��邩�m�F
	if (!m_Model->GetIsLoaded())
	{
		static int flag = 0;
		if (flag != 0) { return; }
		string str = string("���f�����ǂݍ��܂�Ă��܂���\n�^�O�����Ă��Ȃ��\��������܂�\n") + m_ModelName;
		flag = MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("meshRenderer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	D3DXMATRIX m = m_AttachObject->GetWorldMatrix();
	Renderer::SetWorldMatrix(&m);

	// ���f���`��
	m_Model->Draw();
}

/*******************************************************************************
*	���f���ύX
*******************************************************************************/
void ModelRenderer::SetModel(string ModelName)
{
	m_ModelName = ModelName;

	m_Model = ModelContainer::GetModel_InName(m_ModelName);
}
