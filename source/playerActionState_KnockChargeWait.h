/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�@���`���[�W���X�e�[�g�N���X	[ playerActionState_KnockChargeWait.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_KnockChargeWait : public PlayerActionStateBase
{
public:
	PlayerActionState_KnockChargeWait(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::KnockChargeWait) {}

	void Update() override;
	void LateUpdate() override;
};
