/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション小範囲回転ステートクラス	[ playerAnimationState_ShortRoll.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerAnimationStateBase.h"

class PlayerAnimationState_ShortRoll : public PlayerAnimationStateBase
{
protected:
	static inline const float m_FIRST_ROTATE_SPEED = 720.0f;
	static inline const float m_MAX_ROTATE_SPEED = 1080.0f;
	static inline const float m_ROTATE_ACC_RATE = 100.0f;
	static inline const float m_ROTATE_INTERPOLATION_RATE = 0.1f;
	static inline const float m_END_ROTATE_INTERPOLATION_RATE = 0.3f;
	static inline const float m_END_ROTATE_THRESHOLD = 0.1f;

	static inline const float m_SCALE_INTERPOLATION_RATE = 0.3f;
	static inline const float m_SCALE_INTERPOLATION_THRESHOLD = 0.01f;

	float m_RotateSpeed = 0.0f;
	float m_RotateTargetSpeed = m_FIRST_ROTATE_SPEED;

	bool m_IsEndRotate = false;
	bool m_IsEndScaling = false;

public:
	PlayerAnimationState_ShortRoll(PlayerManager* Manager, PlayerManager::AnimationStateId AnimationStateId, AnimationBaseParam Parameter)
		: PlayerAnimationStateBase(Manager, AnimationStateId, Parameter)
	{
		m_IsCameraRotate = false;
	}

	virtual void MainAnimation() = 0;
	virtual void PreEndAnimation() = 0;

	void MainRodRotate(D3DXVECTOR3 Axis);
	void PreEndRodRotate(bool IsLeftTurn, D3DXVECTOR3 Axis);

	void MainScaleChange();
	void PreEndScaleChange();
};
