/*******************************************************************************
*
*	タイトル：	プレイヤー棒出しステートクラス	[ playerActionState_RodScaling.cpp ]
*
*	作成者：	古本 泰隆
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
