/*******************************************************************************
*
*	タイトル：	プレイヤー振り向きステートクラス	[ playerActionState_Turn.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_Turn.h"
#include "collisionContactRecorder_PlayerGround.h"

PlayerActionState_Turn::PlayerActionState_Turn(PlayerManager* Manager)
	: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::Turn)
{
	m_Param->m_TurnSpeed = m_TURN_SPEED;
	m_Param->m_MoveMagnitudeMax = m_LOW_MOVE_SPEED;
	m_Param->m_MoveMagnitude = 0.0f;
	if (!m_Param->m_IsExtend)
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None);
	}
	else
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
	}
}

void PlayerActionState_Turn::Update()
{
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Avoid].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodOpen].Tag
	);
	CheckTurnAngle();

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_Turn::LateUpdate()
{
	AddVelocity();
}

void PlayerActionState_Turn::CheckTurnAngle()
{
	if (m_Param->m_MoveAngleDistance <= m_TURN_END_ANGLE_THRESHOLD)
	{
		if (m_Manager->GetRecvActionStateId() == PlayerManager::ActionStateId::Dash)
		{
			m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Dash);
		}
		else
		{
			m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
		}
	}
}
