/*******************************************************************************
*
*	タイトル：	プレイヤー叩きステートクラス	[ playerActionState_Knock.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_Knock : public PlayerActionStateBase
{
public:
	PlayerActionState_Knock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::Knock) {}

	void Update() override;
	void LateUpdate() override;
};
