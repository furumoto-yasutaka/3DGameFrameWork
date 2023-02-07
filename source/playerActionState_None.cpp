/*******************************************************************************
*
*	タイトル：	プレイヤー無しステートクラス	[ playerActionState_None.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_None.h"
#include "collisionContactRecorder_PlayerGround.h"

PlayerActionState_None::PlayerActionState_None(PlayerManager* Manager)
	: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::None)
{
	if (!m_Param->m_IsExtend)
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None);
	}
	else
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
	}
}

void PlayerActionState_None::Update()
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
	CheckTurnOccur();

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_None::LateUpdate()
{
	AddVelocity();
}

void PlayerActionState_None::CheckTurnOccur()
{
	if (m_Param->m_MoveAngleDistance >= m_TURN_OCCUR_ANGLE)
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Turn);
	}
}
