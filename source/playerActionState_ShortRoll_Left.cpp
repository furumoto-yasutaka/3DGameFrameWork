/*******************************************************************************
*
*	タイトル：	プレイヤー小範囲左回転ステートクラス	[ playerActionState_ShortRoll_Left.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_ShortRoll_Left.h"

PlayerActionState_ShortRoll_Left::PlayerActionState_ShortRoll_Left(PlayerManager* Manager)
	: PlayerActionState_ShortRoll(Manager, PlayerManager::ActionStateId::ShortRoll_Left)
{
	m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::ShortRoll_Left);
}

void PlayerActionState_ShortRoll_Left::Update()
{
	ResetIsInput();
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_Z].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_X].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Avoid].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Roll_Left].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodOpen].Tag
	);
	CheckIsInput();

	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_ShortRoll_Left::LateUpdate()
{
	AddVelocity();
}

void PlayerActionState_ShortRoll_Left::ExecRoll_Left(PlayerInputListener::ActionElement* Elem)
{
	m_IsInput = true;
}
