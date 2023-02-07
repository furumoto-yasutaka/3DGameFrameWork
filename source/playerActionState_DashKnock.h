/*******************************************************************************
*
*	タイトル：	プレイヤーダッシュ叩きステートクラス	[ playerActionState_DashKnock.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_DashKnock : public PlayerActionStateBase
{
public:
	PlayerActionState_DashKnock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::DashKnock) {}

	void Update() override;
	void LateUpdate() override;
};
