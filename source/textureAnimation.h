/*******************************************************************************
*
*	�^�C�g���F	�e�N�X�`���A�j���[�V�����R���|�[�l���g	[ textureAnimation.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"
#include "plate2dRenderer.h"
#include "plate3dRenderer.h"

class TextureAnimation : public SystemComponent
{
public:
	// �A�j���[�V�����ݒ�
	enum class AnimationMode
	{
		Loop = 0,		// ���[�v
		Once_ObjectDestroy,	// �A�j���[�V������1�T��폜
		Once_ObjectDisable,	// �A�j���[�V������1�T���A�N�e�B�u��
	};

private:
	AnimationMode	m_Mode = AnimationMode::Loop;	// �A�j���[�V�����ݒ�
	D3DXVECTOR2*	m_TexCoordBegin = NULL;			// �e�N�X�`�����W(�n�_)
	D3DXVECTOR2*	m_TexCoordDistance = NULL;		// �e�N�X�`�����W(�I�_)
	int				m_WidthDiv = NULL;				// ��������
	int				m_HeightDiv = NULL;				// �c������
	int				m_AnimationInterval = NULL;		// �A�j���[�V������i�߂����
	int				m_FrameCount = NULL;			// �t���[���J�E���g

public:
	TextureAnimation(GameObject* AttachObject) : SystemComponent(AttachObject) {}

	void Init(Plate2DRenderer* ConnectComponent, AnimationMode Mode, int AnimationInterval = 1);
	void Init(Plate3DRenderer* ConnectComponent, AnimationMode Mode, int AnimationInterval = 1);
	void Uninit() override {}
	void Update() override;
	void Draw() override {}
};