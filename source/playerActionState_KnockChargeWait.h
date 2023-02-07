/*******************************************************************************
*
*	タイトル：	プレイヤー叩きチャージ中ステートクラス	[ playerActionState_KnockChargeWait.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_KnockChargeWait : public PlayerActionStateBase
{
public:
	PlayerActionState_KnockChargeWait(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::KnockChargeWait) {}

	void Update() override;
	void LateUpdate() override;
};
