/*******************************************************************************
*
*	タイトル：	プレイヤー広範囲回転ステート基底クラス	[ playerActionState_LongRoll.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_LongRoll : public PlayerActionStateBase
{
public:
	PlayerActionState_LongRoll(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId)
		: PlayerActionStateBase(Manager, ActionStateId)
	{}

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
};
