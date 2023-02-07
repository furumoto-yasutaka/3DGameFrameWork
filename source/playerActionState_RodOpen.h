/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�_�W�J�X�e�[�g�N���X	[ playerActionState_RodOpen.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_RodOpen : public PlayerActionStateBase
{
public:
	PlayerActionState_RodOpen(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::RodOpen) {}

	void Update() override;
	void LateUpdate() override;
};
