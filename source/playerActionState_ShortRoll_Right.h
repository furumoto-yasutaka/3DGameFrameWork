/*******************************************************************************
*
*	タイトル：	プレイヤー小範囲右回転ステートクラス	[ playerActionState_ShortRoll_Right.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionState_ShortRoll.h"

class PlayerActionState_ShortRoll_Right : public PlayerActionState_ShortRoll
{
public:
	PlayerActionState_ShortRoll_Right(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void ExecRoll_Right(PlayerInputListener::ActionElement* Elem) override;
};
