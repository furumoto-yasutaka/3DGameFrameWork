/*******************************************************************************
*
*	タイトル：	たまごエネミーノックバックアニメーションクラス	[ eggEnemyAnimationState_KnockBack.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyAnimationState_KnockBack.h"

EggEnemyAnimationState_KnockBack::EggEnemyAnimationState_KnockBack(EggEnemyManager* Manager, AnimationBaseParam Parameter)
	: EggEnemyAnimationStateBase(Manager, EggEnemyManager::AnimationStateId::KnockBack, Parameter)
{
	m_Manager->GetModelRoot()->m_LocalRotation = Math::GetQuaternionIdentity();
}

void EggEnemyAnimationState_KnockBack::MainAnimation()
{
	float amount = m_ROTATE_ANGLE - m_RotatedAngle;
	if (amount > m_ROTATE_ANGLE_INTERPOLATION_THRESHOLD)
	{
		amount *= m_ROTATE_ANGLE_INTERPOLATION_RATE;
	}
	m_RotatedAngle += amount;

	m_Manager->GetModelRoot()->m_LocalRotation *=
		Math::AxisRotation_Degree({ -1.0f, 0.0f, 0.0f }, amount);
}

void EggEnemyAnimationState_KnockBack::PreEndAnimation()
{
	if (m_IsEndAnimation)
	{
		End();
	}
	else
	{
		float amount = m_RotatedAngle;
		if (amount > m_ROTATE_ANGLE_INTERPOLATION_THRESHOLD)
		{
			amount *= m_END_ROTATE_ANGLE_INTERPOLATION_RATE;
		}
		m_RotatedAngle -= amount;

		m_Manager->GetModelRoot()->m_LocalRotation *=
			Math::AxisRotation_Degree({ 1.0f, 0.0f, 0.0f }, amount);
	}
}

void EggEnemyAnimationState_KnockBack::PreEnd()
{
	EggEnemyAnimationStateBase::PreEnd();

	if (m_Manager->GetNextAnimationStateId() != EggEnemyManager::AnimationStateId::KnockBack)
	{
		m_IsEndAnimation = true;
	}
}
