/*******************************************************************************
*
*	タイトル：	プレイヤー中範囲左回転ステートクラス	[ playerActionState_Roll_Left.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionState_Roll.h"

class PlayerActionState_Roll_Left : public PlayerActionState_Roll
{
public:
	PlayerActionState_Roll_Left(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;
};
