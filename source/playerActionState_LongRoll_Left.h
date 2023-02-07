/*******************************************************************************
*
*	タイトル：	プレイヤー広範囲左回転ステートクラス	[ playerActionState_LongRoll_Left.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionState_LongRoll.h"

class PlayerActionState_LongRoll_Left : public PlayerActionState_LongRoll
{
public:
	PlayerActionState_LongRoll_Left(PlayerManager* Manager)
		: PlayerActionState_LongRoll(Manager, PlayerManager::ActionStateId::LongRoll_Left)
	{}

	void Update() override;
	void LateUpdate() override;
};
