/*******************************************************************************
*
*	タイトル：	たまごエネミー怯みアニメーションクラス	[ eggEnemyAnimationState_Wince.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyAnimationStateBase.h"

class EggEnemyAnimationState_Wince : public EggEnemyAnimationStateBase
{
private:
	static const inline float m_SPIN_RADIUS = 20.0f;
	static const inline float m_SPIN_RADIUS_INTERPOLATION_RATE = 0.2f;
	static const inline float m_SPIN_RADIUS_INTERPOLATION_THRESHOLD = 0.01f;
	static const inline float m_SPIN_SPEED = 1.0f;
	static const inline float m_SPIN_DEFORMATION_X = 0.2f;
	static const inline float m_SPIN_DEFORMATION_Z = 0.2f;

	float m_SpinRadius = 0.0f;

public:
	EggEnemyAnimationState_Wince(EggEnemyManager* Manager, AnimationBaseParam Parameter);

	void MainAnimation() override;
	void PreEndAnimation() override;
};
