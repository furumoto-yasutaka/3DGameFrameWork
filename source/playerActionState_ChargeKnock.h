/*******************************************************************************
*
*	タイトル：	プレイヤーため叩きステートクラス	[ playerActionState_ChargeKnock.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_ChargeKnock : public PlayerActionStateBase
{
public:
	PlayerActionState_ChargeKnock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::ChargeKnock) {}

	void Update() override;
	void LateUpdate() override;
};
