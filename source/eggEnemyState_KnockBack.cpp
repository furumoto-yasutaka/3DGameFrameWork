/*******************************************************************************
*
*	タイトル：	たまごエネミーノックバックステートクラス	[ eggEnemyState_KnockBack.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyState_KnockBack.h"

EggEnemyState_KnockBack::EggEnemyState_KnockBack(EggEnemyManager* Manager)
	: EggEnemyStateBase(Manager, EggEnemyManager::AiStateId::KnockBack)
{
	m_CommonParam->m_MoveMagnitude = m_KNOCKBACK_MAGNITUDE;

	m_Manager->RequestNextAnimationState((int)EggEnemyManager::AnimationStateId::KnockBack);
}

void EggEnemyState_KnockBack::Update()
{
	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
}

void EggEnemyState_KnockBack::LateUpdate()
{
	AddVelocity();
}
