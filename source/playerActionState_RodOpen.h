/*******************************************************************************
*
*	タイトル：	プレイヤー棒展開ステートクラス	[ playerActionState_RodOpen.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_RodOpen : public PlayerActionStateBase
{
public:
	PlayerActionState_RodOpen(PlayerManager* Manager)
		: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::RodOpen) {}

	void Update() override;
	void LateUpdate() override;
};
