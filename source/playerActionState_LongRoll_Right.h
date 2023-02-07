/*******************************************************************************
*
*	タイトル：	プレイヤー広範囲右回転ステートクラス	[ playerActionState_LongRoll_Right.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionState_LongRoll.h"

class PlayerActionState_LongRoll_Right : public PlayerActionState_LongRoll
{
public:
	PlayerActionState_LongRoll_Right(PlayerManager* Manager)
		: PlayerActionState_LongRoll(Manager, PlayerManager::ActionStateId::LongRoll_Right)
	{}

	void Update() override;
	void LateUpdate() override;
};
