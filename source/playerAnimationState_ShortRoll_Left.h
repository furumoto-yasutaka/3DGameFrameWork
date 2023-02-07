/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション小範囲左回転ステートクラス	[ playerAnimationState_ShortRoll_Left.h ]
*
*	作成者：	古本 泰隆
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
