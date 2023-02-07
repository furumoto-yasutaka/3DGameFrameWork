/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション中範囲左回転ステートクラス	[ playerAnimationState_Roll_Left.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerAnimationState_Roll.h"

class PlayerAnimationState_Roll_Left : public PlayerAnimationState_Roll
{
public:
	PlayerAnimationState_Roll_Left(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationState_Roll(Manager, PlayerManager::AnimationStateId::Roll_Left, Parameter)
	{}
	~PlayerAnimationState_Roll_Left() override;

	void MainAnimation() override;
	void PreEndAnimation() override;
};
