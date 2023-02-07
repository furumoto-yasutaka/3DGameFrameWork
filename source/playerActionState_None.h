/*******************************************************************************
*
*	タイトル：	プレイヤー無しステートクラス	[ playerActionState_None.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_None : public PlayerActionStateBase
{
private:
	// 振り向きステートに遷移するボーダー
	static inline const float m_TURN_OCCUR_ANGLE = Math::m_PI * 0.51f;

public:
	PlayerActionState_None(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void CheckTurnOccur();	// 振り向きを発生させるか判断
};
