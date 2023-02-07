/*******************************************************************************
*
*	タイトル：	プレイヤー小範囲回転ステート基底クラス	[ playerActionState_ShortRoll.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_ShortRoll : public PlayerActionStateBase
{
protected:
	static inline const float m_WALK_MAGNITUDE = 0.1f;	// ダッシュ加速度
	static inline const float m_JUMP_MAGNITUDE = 0.1f;	// ジャンプ力
	static inline const float m_COOL_TIME = 0.3f;

	bool m_IsInput = false;

public:
	PlayerActionState_ShortRoll(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId);

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	void ResetIsInput();
	void CheckIsInput();
};
