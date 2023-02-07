/*******************************************************************************
*
*	�^�C�g���F	�v���C���[���͈͍���]�X�e�[�g�N���X	[ playerActionState_ShortRoll_Left.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionState_ShortRoll.h"

class PlayerActionState_ShortRoll_Left : public PlayerActionState_ShortRoll
{
public:
	PlayerActionState_ShortRoll_Left(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void ExecRoll_Left(PlayerInputListener::ActionElement* Elem) override;
};
