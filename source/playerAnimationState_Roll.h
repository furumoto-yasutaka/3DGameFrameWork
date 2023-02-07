/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション中範囲回転ステートクラス	[ playerAnimationState_Roll.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerAnimationStateBase.h"

class PlayerAnimationState_Roll : public PlayerAnimationStateBase
{
protected:
	static inline const float m_ROTATE_INTERPOLATION_RATE = 0.03f;
	static inline const float m_ROTATE_THRESHOLD = 0.1f;
	static inline const float m_ROTATE_ANGLE = 360.0f;
	static inline const float m_ROTATE_INTERPOLATION_ANGLE_REF = 550.0f;
	static inline const float m_END_ROTATE_INTERPOLATION_RATE = 0.3f;
	static inline const float m_END_ROTATE_THRESHOLD = 0.1f;

	static inline const float m_SCALE_INTERPOLATION_RATE = 0.3f;
	static inline const float m_SCALE_INTERPOLATION_THRESHOLD = 0.01f;

	float m_RotatedAngle = 0.0f;

	bool m_IsEndRotate = false;
	bool m_IsEndScaling = false;

public:
	PlayerAnimationState_Roll(PlayerManager* Manager, PlayerManager::AnimationStateId AnimationStateId, AnimationBaseParam Parameter)
		: PlayerAnimationStateBase(Manager, AnimationStateId, Parameter)
	{
		m_IsCameraRotate = false;
	}

	virtual void MainAnimation() = 0;
	virtual void PreEndAnimation() = 0;

	void MainRodRotate(D3DXVECTOR3 Axis);
	void PreEndRodRotate();

	void MainScaleChange();
	void PreEndScaleChange();
};
