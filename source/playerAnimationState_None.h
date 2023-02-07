/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�����ҋ@�X�e�[�g�N���X	[ playerAnimationState_None.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerAnimationStateBase.h"

class PlayerAnimationState_None : public PlayerAnimationStateBase
{
public:
	PlayerAnimationState_None(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationStateBase(Manager, PlayerManager::AnimationStateId::None, Parameter)
	{}

	void MainAnimation() override;
	void PreEndAnimation() override;
};
