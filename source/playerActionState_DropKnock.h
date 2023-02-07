/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�����@���X�e�[�g�N���X	[ playerActionState_DropKnock.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_DropKnock : public PlayerActionStateBase
{
public:
	PlayerActionState_DropKnock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::DropKnock) {}

	void Update() override;
	void LateUpdate() override;
};
