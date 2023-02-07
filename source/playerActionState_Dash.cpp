/*******************************************************************************
*
*	タイトル：	プレイヤーダッシュステートクラス	[ playerActionState_Dash.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_Dash.h"

PlayerActionState_Dash::PlayerActionState_Dash(PlayerManager* Manager)
	: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::Dash)
{
	m_Param->m_MoveMagnitudeMax = m_DASH_MAGNITUDE;
	if (!m_Param->m_IsExtend)
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None);
	}
	else
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
	}
}

void PlayerActionState_Dash::Update()
{
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_Z].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_X].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Avoid].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Roll_Left].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Roll_Right].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::KnockChargeWait].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodScaling].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodOpen].Tag
	);
	CheckEnd();
	CheckTurnOccur();

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_Dash::LateUpdate()
{
	AddVelocity();
}

void PlayerActionState_Dash::ExecMove_Z(PlayerInputListener::ActionElement* Elem)
{
	PlayerActionStateBase::ExecMove_Z(Elem);
	if (Elem->Value != 0.0f) { m_IsMoveInputZ = true; }
}
void PlayerActionState_Dash::ExecMove_X(PlayerInputListener::ActionElement* Elem)
{
	PlayerActionStateBase::ExecMove_X(Elem);
	if (Elem->Value != 0.0f) { m_IsMoveInputX = true; }
}

void PlayerActionState_Dash::CheckEnd()
{
	// 入力がなかった時間を記録し、指定時間以上の入力が無かったら無しステートに遷移する
	if (!m_IsMoveInputX && !m_IsMoveInputZ)
	{
		m_InputEndTimeCount -= Time::GetDeltaTimeSec();
		if (m_InputEndTimeCount <= 0.0f)
		{
			m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
		}
	}
	else
	{
		m_InputEndTimeCount = m_INPUT_END_TIME;
	}

	m_IsMoveInputZ = false;
	m_IsMoveInputX = false;
}

void PlayerActionState_Dash::CheckTurnOccur()
{
	if (m_Param->m_MoveAngleDistance >= m_TURN_OCCUR_ANGLE)
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Turn);
	}
}
