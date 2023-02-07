/*******************************************************************************
*
*	�^�C�g���F	�v���C���[���͈͉�]�X�e�[�g���N���X	[ playerActionState_ShortRoll.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerActionState_ShortRoll.h"
#include "collisionContactRecorder_PlayerAttack.h"
#include "obbCollider3d.h"

PlayerActionState_ShortRoll::PlayerActionState_ShortRoll(
	PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId)
	: PlayerActionStateBase(Manager, ActionStateId)
{
	m_Param->m_MoveMagnitudeMax = m_WALK_MAGNITUDE;
	m_Param->m_JumpMagnitude = m_JUMP_MAGNITUDE;
	m_CoolTimeCount = m_COOL_TIME;
}

void PlayerActionState_ShortRoll::ResetIsInput()
{
	m_IsInput = false;
}

void PlayerActionState_ShortRoll::CheckIsInput()
{
	if (!m_IsInput)
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
	}
}
