/*******************************************************************************
*
*	�^�C�g���F	�X�J�C�h�[���p�ÓI�N���X	[ skyDome.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <string>

class Model;

class SkyDome
{
private:
	static string				m_ModelName;	// ���f������(�R���e�i��̖��O)
	static Model*				m_Model;		// ���f���̏ڍ׏��
	static ID3D11VertexShader*	m_VertexShader;	// ���_�V�F�[�_�[
	static ID3D11PixelShader*	m_PixelShader;	// �s�N�Z���V�F�[�_�[
	static ID3D11InputLayout*	m_VertexLayout;	// ���̓��C�A�E�g
	static float				m_Size;			// �T�C�Y

public:
	static void Init();
	static void Uninit();
	static void Draw();
};
