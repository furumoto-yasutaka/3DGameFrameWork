/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション中範囲右回転ステートクラス	[ playerAnimationState_Roll_Right.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerAnimationState_Roll.h"

class PlayerAnimationState_Roll_Right : public PlayerAnimationState_Roll
{
public:
	PlayerAnimationState_Roll_Right(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationState_Roll(Manager, PlayerManager::AnimationStateId::Roll_Right, Parameter)
	{}
	~PlayerAnimationState_Roll_Right() override;

	void MainAnimation() override;
	void PreEndAnimation() override;
};
