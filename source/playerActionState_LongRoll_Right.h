/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�L�͈͉E��]�X�e�[�g�N���X	[ playerActionState_LongRoll_Right.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionState_LongRoll.h"

class PlayerActionState_LongRoll_Right : public PlayerActionState_LongRoll
{
public:
	PlayerActionState_LongRoll_Right(PlayerManager* Manager)
		: PlayerActionState_LongRoll(Manager, PlayerManager::ActionStateId::LongRoll_Right)
	{}

	void Update() override;
	void LateUpdate() override;
};
