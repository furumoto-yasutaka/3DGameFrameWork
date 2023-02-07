/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション小範囲回転ステートクラス	[ playerAnimationState_ShortRoll.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerAnimationState_ShortRoll.h"
#include "playerManager.h"
#include "gameObject.h"
#include "camera.h"
#include "collisionContactRecorder_PlayerAttack.h"

void PlayerAnimationState_ShortRoll::MainRodRotate(D3DXVECTOR3 Axis)
{
	// 棒を回転させる
	m_RotateSpeed += (m_RotateTargetSpeed - m_RotateSpeed) * m_ROTATE_INTERPOLATION_RATE;

	if (m_RotateTargetSpeed < m_MAX_ROTATE_SPEED)
	{
		m_RotateTargetSpeed += m_ROTATE_ACC_RATE * Time::GetDeltaTimeSec();

		if (m_RotateTargetSpeed < m_MAX_ROTATE_SPEED)
		{
			m_RotateTargetSpeed = m_MAX_ROTATE_SPEED;
		}
	}

	GameObject* rodConnection = m_Manager->GetModelParts(PlayerManager::ModelPartsId::RodConnection);
	rodConnection->m_LocalRotation *= Math::AxisRotation_Degree(Axis, m_RotateSpeed * Time::GetDeltaTimeSec());
}

void PlayerAnimationState_ShortRoll::PreEndRodRotate(bool IsLeftTurn, D3DXVECTOR3 Axis)
{
	// 現在の棒の位置から元の棒の位置まで割合補間で移動する
	D3DXVECTOR3 cameraForward = Manager::GetScene()->GetActiveCamera()->GetAttachObject()->GetForward();
	cameraForward = { cameraForward.x, 0.0f, cameraForward.z };
	cameraForward = Math::Normalize(cameraForward);

	GameObject* rodConnection = m_Manager->GetModelParts(PlayerManager::ModelPartsId::RodConnection);
	D3DXVECTOR3 rodForward = rodConnection->GetForward();
	rodForward = { rodForward.x, 0.0f, rodForward.z };
	rodForward = Math::Normalize(rodForward);

	float anglePlayer = atan2f(cameraForward.z, cameraForward.x);
	if (anglePlayer < 0.0f) { anglePlayer += Math::m_PI * 2.0f; }

	float angleRod = atan2f(rodForward.z, rodForward.x);
	if (angleRod < 0.0f) { angleRod += Math::m_PI * 2.0f; }

	float angle = anglePlayer - angleRod;
	if (angle < 0.0f) { angle += Math::m_PI * 2.0f; }
	
	if (!IsLeftTurn)
	{
		angle = Math::m_PI * 2.0f - angle;
	}

	if (angle > m_END_ROTATE_THRESHOLD)
	{
		angle *= m_END_ROTATE_INTERPOLATION_RATE;
	}
	else
	{
		m_IsEndRotate = true;
	}

	rodConnection->m_LocalRotation *= Math::AxisRotation_Radian(Axis, angle);

}

void PlayerAnimationState_ShortRoll::MainScaleChange()
{
	// 棒のスケールを変化させる
	GameObject* obj = m_Manager->GetAttackCollision()->GetAttachObject()->GetParent();
	float amount = (1.0f - obj->m_LocalScale.x);

	if (amount > m_SCALE_INTERPOLATION_THRESHOLD)
	{
		amount *= m_SCALE_INTERPOLATION_RATE;
	}
	obj->m_LocalScale += { amount, amount, amount };
}

void PlayerAnimationState_ShortRoll::PreEndScaleChange()
{
	// 棒のスケールを変化させる
	GameObject* obj = m_Manager->GetAttackCollision()->GetAttachObject()->GetParent();
	float amount = obj->m_LocalScale.x;

	if (amount > m_SCALE_INTERPOLATION_THRESHOLD)
	{
		amount *= m_SCALE_INTERPOLATION_RATE;
	}
	else
	{
		m_IsEndScaling = true;
	}

	obj->m_LocalScale -= { amount, amount, amount };
}
