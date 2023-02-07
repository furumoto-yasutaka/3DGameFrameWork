/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�@���X�e�[�g�N���X	[ playerActionState_Knock.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_Knock : public PlayerActionStateBase
{
public:
	PlayerActionState_Knock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::Knock) {}

	void Update() override;
	void LateUpdate() override;
};
