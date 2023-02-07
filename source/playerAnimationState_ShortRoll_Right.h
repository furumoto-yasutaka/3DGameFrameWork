/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�������͈͉E��]�X�e�[�g�N���X	[ playerAnimationState_ShortRoll_Right.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerAnimationState_ShortRoll.h"

class PlayerAnimationState_ShortRoll_Right : public PlayerAnimationState_ShortRoll
{
public:
	PlayerAnimationState_ShortRoll_Right(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationState_ShortRoll(Manager, PlayerManager::AnimationStateId::ShortRoll_Right, Parameter)
	{}

	void MainAnimation() override;
	void PreEndAnimation() override;
};
