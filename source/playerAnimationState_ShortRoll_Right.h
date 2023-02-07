/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション小範囲右回転ステートクラス	[ playerAnimationState_ShortRoll_Right.h ]
*
*	作成者：	古本 泰隆
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
