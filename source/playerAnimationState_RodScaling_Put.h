/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション棒納めステートクラス	[ playerAnimationState_RodScaling_Put.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerAnimationStateBase.h"

class PlayerAnimationState_RodScaling_Put : public PlayerAnimationStateBase
{
private:
	static inline const float m_PUT_LENGTH = 2.5f;
	static inline const float m_PUT_THRESHOLD = 0.1f;
	static inline const float m_PUT_INTERPOLATION_SPEED = 0.2f;

	float m_PutLength = 0.0f;

public:
	PlayerAnimationState_RodScaling_Put(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationStateBase(Manager, PlayerManager::AnimationStateId::RodScaling_Put, Parameter)
	{}
	~PlayerAnimationState_RodScaling_Put() override;

	void MainAnimation() override;
	void PreEndAnimation() override;
};
