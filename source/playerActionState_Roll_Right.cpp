/*******************************************************************************
*
*	タイトル：	プレイヤー中範囲右回転ステートクラス	[ playerActionState_Roll_Right.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_Roll_Right.h"

PlayerActionState_Roll_Right::PlayerActionState_Roll_Right(PlayerManager* Manager)
	: PlayerActionState_Roll(Manager, PlayerManager::ActionStateId::Roll_Right)
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::Roll_Right);
}

void PlayerActionState_Roll_Right::Update()
{
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_Z].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_X].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Avoid].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodOpen].Tag
	);

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_Roll_Right::LateUpdate()
{
	AddVelocity();
}
