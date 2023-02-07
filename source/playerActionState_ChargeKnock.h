/*******************************************************************************
*
*	�^�C�g���F	�v���C���[���ߒ@���X�e�[�g�N���X	[ playerActionState_ChargeKnock.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_ChargeKnock : public PlayerActionStateBase
{
public:
	PlayerActionState_ChargeKnock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::ChargeKnock) {}

	void Update() override;
	void LateUpdate() override;
};
