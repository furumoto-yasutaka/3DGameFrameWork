/*******************************************************************************
*
*	�^�C�g���F	�摜�_�ŃX�N���v�g	[ blinkImage.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class BlinkImage : public ScriptComponent
{
public:
	// �_�ŕ��@
	enum class BlinkMode
	{
		None = 0,
		Fade,
	};
	// �_�ł̐i�s��
	enum class BlinkState
	{
		Visible = 0,
		ChangeInVisible,
		InVisible,
		ChangeVisible,
	};

private:
	BlinkMode	m_Mode;								// �_�ŕ��@
	BlinkState	m_State;							// �_�ł̐i�s��
	float		m_TimeCountSec = 0.0f;				// ���Ԍv��(�b)
	float		m_VisibleTimeSec = 0.0f;			// �\���̌p������
	float		m_InVisibleTimeSec = 0.0f;			// ��\���̌p������
	
	float		m_ChangeVisibleTimeSec = 0.0f;		// �\���ɂ����鎞��
	float		m_ChangeInVisibleTimeSec = 0.0f;	// ��\���ɂ����鎞��

public:
	BlinkImage(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init(BlinkMode Mode, float VisibleTimeSec, float InVisibleTimeSec,
			float ChangeVisibleTimeSec = 0.0f, float ChangeInVisibleTimeSec = 0.0f);
	void Uninit() override {}
	void Update() override;
	void Draw() override {}

private:
	// �����x�ύX
	void ChangeAlpha();
	// �����x�ύX(�t�F�[�h���[�h)
	void ChangeAlpha_Fade();

	// �_�ŏ󋵕ύX
	void ChangeState();
	// �_�ŏ󋵕ύX(���ݒ胂�[�h)
	void ChangeState_None();
	// �_�ŏ󋵕ύX(�t�F�[�h���[�h)
	void ChangeState_Fade();
};
