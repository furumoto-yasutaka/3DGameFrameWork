/*******************************************************************************
*
*	�^�C�g���F	�e�N�X�`���Ǘ��p�ÓI�N���X	[ textureContainer.h ]
*	�� ���f���ɕt�����Ă���e�N�X�`���͊Ǘ��Ɋ܂݂܂���
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "texture.h"

#include <unordered_map>
#include <memory>

class TextureContainer
{
private:
	// ���v�f
	// ����1	string�^	�e�N�X�`������(�L�[)
	// ����2	Texture*�^	�e�N�X�`�����
	static inline unordered_map<string, Texture*> m_TextureInfo;	// �e�N�X�`�����X�g

public:
	static void Init();
	static void Uninit();

	// ���ׂẴe�N�X�`���ɑ΂��Ďg�p�t���O�ɉ�����
	// ���[�h�E�A�����[�h�����s(�V�[���ύX���p)
	static void LoadAndUnload_AllTexture();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//

	// �e�N�X�`���擾(���̂Ō���)
	static Texture* GetTexture_InName(string Name);
	/////////////////////////////
private:
	// �e�N�X�`���ǉ�
	static void AddTexture(string Name, string Path,
						int WidthDiv, int HeightDiv, int Tag);
};
