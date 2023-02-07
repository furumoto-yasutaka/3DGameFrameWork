/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�L�͈͍���]�X�e�[�g�N���X	[ playerActionState_LongRoll_Left.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionState_LongRoll.h"

class PlayerActionState_LongRoll_Left : public PlayerActionState_LongRoll
{
public:
	PlayerActionState_LongRoll_Left(PlayerManager* Manager)
		: PlayerActionState_LongRoll(Manager, PlayerManager::ActionStateId::LongRoll_Left)
	{}

	void Update() override;
	void LateUpdate() override;
};
