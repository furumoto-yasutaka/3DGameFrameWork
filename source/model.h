/*******************************************************************************
*
*	�^�C�g���F	���f���N���X	[ model.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "renderer.h"
#include "texture.h"

// �}�e���A���\����
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	Texture*					Tex;
};

// �`��T�u�Z�b�g�\����
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};

// ���f���\����
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};

class Model
{
private:
	char			m_Path[256];			// ���΃p�X
	int				m_Tag = 0;				// �g�p����V�[����\���r�b�g�t���O
	bool			m_IsLoaded = false;		// ���[�h��

	ID3D11Buffer*	m_VertexBuffer = NULL;	// ���_�o�b�t�@
	ID3D11Buffer*	m_IndexBuffer = NULL;	// �C���f�b�N�X�o�b�t�@

	SUBSET*			m_SubsetArray = NULL;	// �T�u�Z�b�g
	unsigned int	m_SubsetNum = NULL;		// �T�u�Z�b�g��

public:
	Model() = delete;
	Model(const char* Path) { strcpy(m_Path, Path); }

	void Draw();

	// ���[�h
	void Load();

	// �A�����[�h
	void Unload(bool TexDelete = false);
	
	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	char* GetPath() { return m_Path; }

	int GetTag() { return m_Tag; }
	void AddTag(int Tag) { m_Tag |= Tag; }

	bool GetIsLoaded() { return m_IsLoaded; }
	/////////////////////////////
private:
	// obj�t�@�C���ǂݍ���
	void LoadObj(const char* FileName, MODEL* Model);

	// mtl�t�@�C���ǂݍ���
	void LoadMaterial(const char* FileName, MODEL_MATERIAL** MaterialArray, unsigned int* MaterialNum);
};
