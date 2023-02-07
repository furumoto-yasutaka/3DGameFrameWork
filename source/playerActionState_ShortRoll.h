/*******************************************************************************
*
*	�^�C�g���F	�v���C���[���͈͉�]�X�e�[�g���N���X	[ playerActionState_ShortRoll.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_ShortRoll : public PlayerActionStateBase
{
protected:
	static inline const float m_WALK_MAGNITUDE = 0.1f;	// �_�b�V�������x
	static inline const float m_JUMP_MAGNITUDE = 0.1f;	// �W�����v��
	static inline const float m_COOL_TIME = 0.3f;

	bool m_IsInput = false;

public:
	PlayerActionState_ShortRoll(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId);

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	void ResetIsInput();
	void CheckIsInput();
};
