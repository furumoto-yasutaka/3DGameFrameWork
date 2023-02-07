/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�L�͈͉�]�X�e�[�g���N���X	[ playerActionState_LongRoll.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_LongRoll : public PlayerActionStateBase
{
public:
	PlayerActionState_LongRoll(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId)
		: PlayerActionStateBase(Manager, ActionStateId)
	{}

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
};
