/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション棒出しステートクラス	[ playerAnimationState_None_Extend.h ]
*
*	作成者：	古本 泰隆
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
