/*******************************************************************************
*
*	タイトル：	プレイヤー小範囲右回転ステートクラス	[ playerActionState_ShortRoll_Right.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_ShortRoll_Right.h"

PlayerActionState_ShortRoll_Right::PlayerActionState_ShortRoll_Right(PlayerManager* Manager)
	: PlayerActionState_ShortRoll(Manager, PlayerManager::ActionStateId::ShortRoll_Left)
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::ShortRoll_Right);
}

void PlayerActionState_ShortRoll_Right::Update()
{
	ResetIsInput();
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_Z].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_X].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Avoid].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Roll_Right].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodOpen].Tag
	);
	CheckIsInput();

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_ShortRoll_Right::LateUpdate()
{
	AddVelocity();
}

void PlayerActionState_ShortRoll_Right::ExecRoll_Right(PlayerInputListener::ActionElement* Elem)
{
	m_IsInput = true;
}
