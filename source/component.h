/*******************************************************************************
*
*	�^�C�g���F	�R���|�[�l���g���N���X	[ component.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "callbackListner.h"

#include <list>

class GameObject;
class ComponentDebugInfo;

class Component
{
public:
	// �R���|�[�l���g�̕���
	enum class ProcGroup
	{
		System = 0,	// �`��𔺂�Ȃ�����
		Script,		// �X�N���v�g
		Draw3D,		// 3D�`��𔺂�����
		Draw2D,		// 2D�`��𔺂�����
		Physics,	// ����
		Length,
	};

protected:
	GameObject* m_AttachObject;						// �A�^�b�`��I�u�W�F�N�g
	ProcGroup	m_ProcGroup = ProcGroup::System;	// �����O���[�v
	bool		m_Active = true;					// �A�N�e�B�u�t���O
	bool		m_Destroy = false;					// �폜�t���O

public:
	Component() = delete;
	Component(GameObject* AttachObject) : m_AttachObject(AttachObject) {}

	virtual void LateInit() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() {}
	virtual void Draw() = 0;

	// ���g�̍폜��\��
	virtual void SetDestroy() { m_Destroy = true; }

	// �폜����
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	GameObject* GetAttachObject() { return m_AttachObject; }

	ProcGroup GetProcGroup() { return m_ProcGroup; }

	bool GetActive() { return m_Active; }
	void SetActive(bool value) { m_Active = value; }
	/////////////////////////////

#ifdef _DEBUG
	// �f�o�b�O���\���p
	virtual ComponentDebugInfo* GetComponentDebugInfo() { return NULL; }
#endif
};
