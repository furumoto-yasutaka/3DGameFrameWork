/*******************************************************************************
*
*	タイトル：	プレイヤー振り向きステートクラス	[ playerActionState_Turn.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_Turn : public PlayerActionStateBase
{
private:
	static inline const float m_TURN_SPEED = 0.5f;					// 振り向き速度
	static inline const float m_LOW_MOVE_SPEED = 0.1f;				// ダッシュ加速度
	static inline const float m_TURN_END_ANGLE_THRESHOLD = 0.1f;	// 振り向きを終了とする角度

public:
	PlayerActionState_Turn(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void CheckTurnAngle();	// 振り向きを終了するか確認
};
