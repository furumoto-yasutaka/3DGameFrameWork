/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�������͈͍���]�X�e�[�g�N���X	[ playerAnimationState_ShortRoll_Left.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerAnimationState_ShortRoll.h"

class PlayerAnimationState_ShortRoll_Left : public PlayerAnimationState_ShortRoll
{
public:
	PlayerAnimationState_ShortRoll_Left(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationState_ShortRoll(Manager, PlayerManager::AnimationStateId::ShortRoll_Left, Parameter)
	{}

	void MainAnimation() override;
	void PreEndAnimation() override;
};
