/*******************************************************************************
*
*	タイトル：	プレイヤー中範囲回転ステート基底クラス	[ playerActionState_Roll.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_Roll.h"
#include "collisionContactRecorder_PlayerAttack.h"
#include "obbCollider3d.h"

PlayerActionState_Roll::PlayerActionState_Roll(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId)
	: PlayerActionStateBase(Manager, ActionStateId)
{
	m_Param->m_MoveMagnitudeMax = m_WALK_MAGNITUDE;
	m_Param->m_JumpMagnitude = m_JUMP_MAGNITUDE;
	m_Param->m_JumpMagnitude = m_JUMP_MAGNITUDE;
	m_CoolTimeCount = m_COOL_TIME;
}
