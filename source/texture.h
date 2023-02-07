/*******************************************************************************
*
*	�^�C�g���F	�e�N�X�`���N���X	[ texture.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"

class Texture
{
private:
	char						m_Path[256];				// ���΃p�X
	int							m_Tag = 0;					// �g�p����V�[����\���r�b�g�t���O
	ID3D11ShaderResourceView*	m_TextureResource = NULL;	// �e�N�X�`�����\�[�X
	bool						m_IsLoaded = false;			// ���[�h��
	int							m_WidthDiv = 1;				// ��������
	int							m_HeightDiv = 1;			// �c������

public:
	Texture() = delete;
	Texture(const char* Path) { strcpy(m_Path, Path); }
	
	// ���[�h
	void Load();

	// �A�����[�h
	void Unload();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	char* GetPath() { return m_Path; }
	void SetPath(char* path) { strcpy(m_Path, path); }

	int GetTag() { return m_Tag; }
	void AddTag(int Tag) { m_Tag |= Tag; }

	ID3D11ShaderResourceView* GetResource() { return m_TextureResource; }

	bool GetIsLoaded() { return m_IsLoaded; }

	int GetWidthDiv() { return m_WidthDiv; }
	void SetWidthDiv(int WidthDiv) { m_WidthDiv = WidthDiv; }

	int GetHeightDiv() { return m_HeightDiv; }
	void SetHeightDiv(int HeightDiv) { m_HeightDiv = HeightDiv; }
	/////////////////////////////
};
