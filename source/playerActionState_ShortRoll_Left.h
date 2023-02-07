/*******************************************************************************
*
*	タイトル：	プレイヤー小範囲左回転ステートクラス	[ playerActionState_ShortRoll_Left.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionState_ShortRoll.h"

class PlayerActionState_ShortRoll_Left : public PlayerActionState_ShortRoll
{
public:
	PlayerActionState_ShortRoll_Left(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void ExecRoll_Left(PlayerInputListener::ActionElement* Elem) override;
};
