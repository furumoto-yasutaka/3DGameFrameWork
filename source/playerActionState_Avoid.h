/*******************************************************************************
*
*	タイトル：	プレイヤー回避ステートクラス	[ playerActionState_Avoid.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerActionStateBase.h"

class PlayerActionState_Avoid : public PlayerActionStateBase
{
private:
	static inline const float m_COOL_TIME = 0.1f;
	static inline const float m_MOVE_LENGTH = 5.0f;
	static inline const float m_MOVE_SPEED_RATE = 0.05f;
	static inline const float m_MOVE_SPEED_VALUE = 10.0f;
	static inline const float m_MOVE_THRESHOLD = 0.0001f;

	D3DXVECTOR3		m_TargetAngle;
	float			m_MoveTotalAmount = 0.0f;
	optional<float>	m_CorrectionAngleX;
	optional<float>	m_CorrectionAngleZ;

public:
	PlayerActionState_Avoid(PlayerManager* Manager);

	void Update() override;
	void LateUpdate() override;
	bool CheckElemContinue(bool IsCanExec, int Id) override;

	void ExecMove_Z(PlayerInputListener::ActionElement* Elem) override;
	void ExecMove_X(PlayerInputListener::ActionElement* Elem) override;
	void ExecJump(PlayerInputListener::ActionElement* Elem) override;

	void InitAvoid();
	void UpdateAvoid();

	void SetCorrectionAngleX(float Value);	// 回避補正先角度の設定(X)
	void SetCorrectionAngleZ(float Value);	// 回避補正先角度の設定(Z)
	void CorrectionAvoidAngle();			// 回避方向の補正
};
