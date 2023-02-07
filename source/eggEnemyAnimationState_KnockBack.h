/*******************************************************************************
*
*	タイトル：	たまごエネミーノックバックアニメーションクラス	[ eggEnemyAnimationState_KnockBack.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyAnimationStateBase.h"

class EggEnemyAnimationState_KnockBack : public EggEnemyAnimationStateBase
{
private:
	static inline const float m_ROTATE_ANGLE = 30.0f;							// 傾く角度
	static inline const float m_ROTATE_ANGLE_INTERPOLATION_RATE = 0.2f;			// 1フレーム当たりの傾きの補間割合
	static inline const float m_ROTATE_ANGLE_INTERPOLATION_THRESHOLD = 0.01f;	// 補間終了のしきい値

	static inline const float m_END_ROTATE_ANGLE_INTERPOLATION_RATE = 0.1f;		// 1フレーム当たりの傾きの補間割合

	float m_RotatedAngle = 0.0f;
	bool m_IsEndAnimation = false;

public:
	EggEnemyAnimationState_KnockBack(EggEnemyManager* Manager, AnimationBaseParam Parameter);

	void MainAnimation() override;
	void PreEndAnimation() override;

	void PreEnd() override;
};
