/*******************************************************************************
*
*	�^�C�g���F	�v���C���[���͈͉E��]�X�e�[�g�N���X	[ playerActionState_ShortRoll_Right.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerActionState_ShortRoll.h"

class PlayerActionState_ShortRoll_Right : public PlayerActionState_ShortRoll
{
public:
	PlayerActionState_ShortRoll_Right(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void ExecRoll_Right(PlayerInputListener::ActionElement* Elem) override;
};
