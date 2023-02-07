/*******************************************************************************
*
*	タイトル：	プレイヤー中範囲回転ステート基底クラス	[ playerActionState_Roll.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_Roll : public PlayerActionStateBase
{
private:
	static inline const float m_WALK_MAGNITUDE = 0.1f;	// ダッシュ加速度
	static inline const float m_JUMP_MAGNITUDE = 0.1f;	// ジャンプ力
	static inline const float m_COOL_TIME = 0.3f;

public:
	PlayerActionState_Roll(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId);

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
};
