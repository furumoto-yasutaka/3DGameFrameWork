/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�_�o���X�e�[�g�N���X	[ playerActionState_RodScaling.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_RodScaling : public PlayerActionStateBase
{
public:
	PlayerActionState_RodScaling(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;
};
