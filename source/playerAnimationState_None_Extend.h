/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�����_�o���X�e�[�g�N���X	[ playerAnimationState_None_Extend.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerAnimationStateBase.h"

class PlayerAnimationState_None_Extend : public PlayerAnimationStateBase
{
public:
	PlayerAnimationState_None_Extend(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationStateBase(Manager, PlayerManager::AnimationStateId::None_Extend, Parameter)
	{}

	void MainAnimation() override;
	void PreEndAnimation() override;
};
