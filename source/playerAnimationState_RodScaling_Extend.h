/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�����_�o���X�e�[�g�N���X	[ playerAnimationState_RodScaling_Extend.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "playerAnimationStateBase.h"

class PlayerAnimationState_RodScaling_Extend : public PlayerAnimationStateBase
{
private:
	static inline const float m_EXTEND_LENGTH = 2.5f;
	static inline const float m_EXTEND_THRESHOLD = 0.1f;
	static inline const float m_EXTEND_INTERPOLATION_SPEED = 0.2f;

	float m_ExtendedLength = 0.0f;

public:
	PlayerAnimationState_RodScaling_Extend(PlayerManager* Manager, AnimationBaseParam Parameter)
		: PlayerAnimationStateBase(Manager, PlayerManager::AnimationStateId::RodScaling_Extend, Parameter)
	{}
	~PlayerAnimationState_RodScaling_Extend() override;

	void MainAnimation() override;
	void PreEndAnimation() override;
};
