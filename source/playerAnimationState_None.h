/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション待機ステートクラス	[ playerAnimationState_None.h ]
*
*	作成者：	古本 泰隆
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
