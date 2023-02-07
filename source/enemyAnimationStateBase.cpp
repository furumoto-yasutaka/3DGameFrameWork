/*******************************************************************************
*
*	タイトル：	エネミーアニメーションステート基底クラス	[ enemyAnimationStateBase.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "enemyAnimationStateBase.h"
#include "enemyManager.h"
#include "gameObject.h"

void EnemyAnimationStateBase::Update()
{
	switch (m_AnimationStepId)
	{
		using enum AnimationStepId;
	case Main:
		MainAnimation();
		break;
	case PreEnd:
		PreEndAnimation();
		break;
	default: break;
	}
}

void EnemyAnimationStateBase::LateUpdate()
{
	if (m_AnimationBaseParam.IsBodyRotate)
	{
		D3DXVECTOR3 vel = m_BaseManager->GetCommonParameter()->m_Velocity;
		vel.y = 0.0f;
		float moveSpeed = D3DXVec3Length(&vel);

		UpdateBodyRotate(moveSpeed);
	}
}

void EnemyAnimationStateBase::PreEnd()
{
	if (m_AnimationStepId != AnimationStepId::End)
	{
		m_AnimationStepId = AnimationStepId::PreEnd;
	}
}

void EnemyAnimationStateBase::End()
{
	m_AnimationStepId = AnimationStepId::End;
}

void EnemyAnimationStateBase::UpdateBodyRotate(float MoveSpeed)
{
	m_AnimationBaseParam.RotateTargetAngle = MoveSpeed * m_ROTATE_ANGLE_RATE;
	if (m_AnimationBaseParam.RotateTargetAngle > m_ROTATE_ANGLE_MAX)
	{
		m_AnimationBaseParam.RotateTargetAngle = m_ROTATE_ANGLE_MAX;
	}

	m_AnimationBaseParam.RotateAngle +=
		(m_AnimationBaseParam.RotateTargetAngle - m_AnimationBaseParam.RotateAngle) * m_ROTATE_INTERPOLATION_RATE;

	m_BaseManager->GetModelRoot()->m_LocalRotation = 
		Math::AxisRotation_Degree({ 1.0f, 0.0f, 0.0f }, -m_AnimationBaseParam.RotateAngle);
}
