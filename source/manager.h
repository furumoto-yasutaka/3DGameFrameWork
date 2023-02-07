/*******************************************************************************
*
*	�^�C�g���F	�Q�[���S�̊Ǘ��p�ÓI�N���X	[ manager.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "scene.h"
#include "transition.h"

class Manager
{
public:
	static inline Scene* m_Scene = NULL;		// �V�[���̃C���X�^���X
	static inline Scene* m_NextScene = NULL;	// �\��p�V�[���̃C���X�^���X

public:
	static void Init(HINSTANCE hInstance);
	static void Uninit();
	static void Update();
	static void Draw();

	// ���̃V�[����\��
	template<class T>
	static void SetScene(Transition::TransitionOption Info)
	{
		m_NextScene = DBG_NEW T();

		if (m_Scene)
		{// �V�[�������݂���ꍇ
			// �ʏ�̑J��
			Transition::StartTransitionOut(Info);
		}
		else
		{// �V�[�������݂��Ȃ��ꍇ
			// �Q�[���N������Ƃ������ƂȂ̂Ńt�F�[�h�A�E�g�͂����A�J�ڐݒ�𔽉f����
			Transition::SetTransitionOption(Info);
		}
	}

	// �V�[���J�ڂ��s�����m�F
	static void CheckScene();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	static Scene* GetScene() { return m_Scene; }
	/////////////////////////////
};
