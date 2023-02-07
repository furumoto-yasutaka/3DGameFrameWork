/*******************************************************************************
*
*	タイトル：	プレイヤー落下叩きステートクラス	[ playerActionState_DropKnock.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_DropKnock : public PlayerActionStateBase
{
public:
	PlayerActionState_DropKnock(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::DropKnock) {}

	void Update() override;
	void LateUpdate() override;
};
