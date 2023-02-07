/*******************************************************************************
*
*	タイトル：	プレイヤー棒出しステートクラス	[ playerActionState_RodScaling.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_RodScaling : public PlayerActionStateBase
{
public:
	PlayerActionState_RodScaling(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;
};
