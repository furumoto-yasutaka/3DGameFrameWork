/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�_�b�V���@���X�e�[�g�N���X	[ playerActionState_DashKnock.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_DashKnock : public PlayerActionStateBase
{
public:
	PlayerActionState_DashKnock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::DashKnock) {}

	void Update() override;
	void LateUpdate() override;
};
