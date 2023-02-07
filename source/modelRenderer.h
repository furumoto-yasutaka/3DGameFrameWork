/*******************************************************************************
*
*	�^�C�g���F	���f���`��R���|�[�l���g	[ modelRenderer.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "draw3dComponent.h"

#include <string>

class Model;

class ModelRenderer : public Draw3DComponent
{
private:
	string				m_ModelName;			// ���f���̖���(�R���e�i��̖��O)
	string				m_VertexShaderName;		// ���_�V�F�[�_�[��
	string				m_PixelShaderName;		// �s�N�Z���V�F�[�_�[��
	Model*				m_Model = NULL;			// ���f���̏ڍ׏��
	ID3D11VertexShader* m_VertexShader = NULL;	// ���_�V�F�[�_�[
	ID3D11PixelShader*	m_PixelShader = NULL;	// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*	m_VertexLayout = NULL;	// ���̓��C�A�E�g

public:
	ModelRenderer(GameObject* AttachObject) : Draw3DComponent(AttachObject) {}

	void Init(const char* ModelName, string VertexShaderName = "vertexLightingVS", string PixelShaderName = "vertexLightingPS");
	void Uninit() override;
	void Update() override;
	void Draw() override;

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	void SetModel(string ModelName);
	/////////////////////////////
};
