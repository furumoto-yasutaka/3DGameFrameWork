/*******************************************************************************
*
*	�^�C�g���F	���f���Ǘ��p�ÓI�N���X	[ modelContainer.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
* 
*******************************************************************************/
#pragma once
#include "model.h"

#include <unordered_map>

class ModelContainer
{
private:
	// ���v�f
	// ����1	string�^	���f������(�L�[)
	// ����2	Model*�^	���f�����
	static inline unordered_map<string, Model*> m_ModelInfo;	// ���f�����X�g

public:
	static void Init();
	static void Uninit();

	// ���ׂẴ��f���ɑ΂��ă^�O�ɉ�����
	// ���[�h�E�A�����[�h�����s(�V�[���ύX���p)
	static void LoadAndUnload_AllModel();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//

	// ���f���擾(���̂Ō���)
	static Model* GetModel_InName(string Name);
	/////////////////////////////
private:
	// ���f���ǉ�
	static void AddModel(string Name, string Path, int Tag);
};
