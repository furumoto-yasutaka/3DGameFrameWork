/*******************************************************************************
*
*	タイトル：	プレイヤー中範囲右回転ステートクラス	[ playerActionState_Roll_Right.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionState_Roll.h"

class PlayerActionState_Roll_Right : public PlayerActionState_Roll
{
public:
	PlayerActionState_Roll_Right(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;
};
