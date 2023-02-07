/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�_�o���X�e�[�g�N���X	[ playerActionState_RodScaling.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerActionState_RodScaling.h"

PlayerActionState_RodScaling::PlayerActionState_RodScaling(PlayerManager* Manager)
	: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::RodScaling)
{
	if (m_Param->m_IsExtend)
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::RodScaling_Put);
	}
	else
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::RodScaling_Extend);
	}

	m_Param->m_IsExtend = !m_Param->m_IsExtend;
}

void PlayerActionState_RodScaling::Update()
{
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_Z].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_X].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Avoid].Tag
	);

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_RodScaling::LateUpdate()
{
	AddVelocity();
}
