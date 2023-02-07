/*******************************************************************************
*
*	�^�C�g���F	�v���C���[���͎�t�X�N���v�g	[ playerInputListener_MouseKeyboard.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerInputListener.h"

#include <optional>

class PlayerInputListener_MouseKeyboard : public PlayerInputListener
{
//public:
//	enum class InputWASD
//	{
//		W = (1 << 0),
//		A = (1 << 1),
//		S = (1 << 2),
//		D = (1 << 3),
//	};
//
//private:
//	static inline const float m_DOUBLE_PUSH_WAIT_TIME = 0.4f;
//
//	optional<float> m_DoublePushWaitTimeCount_Avoid[4];

public:
	PlayerInputListener_MouseKeyboard(PlayerManager* Manager) : PlayerInputListener(Manager) {}

//	void UpdateQueue() override;	// �폜�\��̃L���[�̍폜�Ɠ��͂̎擾���s��
//
//private:
//	void UpdateDoublePushWaitTime();

	// ���͎擾
	float InputMove_Z() override;			// �ړ�����(�O��)
	float InputMove_X() override;			// �ړ�����(���E)
	bool InputJump() override;				// �W�����v����
	bool InputAvoid() override;				// ������
	optional<float> InputRoll_L() override;	// ���͈͉�]����
	optional<float> InputRoll_R() override;	// ���͈͉�]����
	bool InputKnock() override;				// �@������(�_�b�V���@���E�����@���܂�)
	bool InputKnockChargeWait() override;	// ���ߒ@������
	bool InputRodScaling() override;		// �_�g�k����
	bool InputRodOpen() override;			// �_�W�J����
};
