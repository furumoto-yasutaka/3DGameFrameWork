/*******************************************************************************
*
*	タイトル：	プレイヤーダッシュステートクラス	[ playerActionState_Dash.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_Dash : public PlayerActionStateBase
{
private:
	static inline const float m_TURN_OCCUR_ANGLE = Math::m_PI * 0.51f;
	static inline const float m_DASH_MAGNITUDE = 0.3f;						// ダッシュ加速度
	static inline const float m_INPUT_END_TIME = 0.2f;

	bool m_IsMoveInputX = false;
	bool m_IsMoveInputZ = false;
	float m_InputEndTimeCount = m_INPUT_END_TIME;

public:
	PlayerActionState_Dash(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void ExecMove_Z(PlayerInputListener::ActionElement* Elem) override;
	void ExecMove_X(PlayerInputListener::ActionElement* Elem) override;

	void CheckEnd();		// ダッシュの終了条件を満たすか確認
	void CheckTurnOccur();	// 振り向きを発生させるか判断
};
