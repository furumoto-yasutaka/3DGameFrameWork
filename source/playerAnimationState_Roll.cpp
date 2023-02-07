/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーション中範囲回転ステートクラス	[ playerAnimationState_Roll.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerAnimationState_Roll.h"
#include "playerManager.h"
#include "gameObject.h"
#include "camera.h"
#include "collisionContactRecorder_PlayerAttack.h"

void PlayerAnimationState_Roll::MainRodRotate(D3DXVECTOR3 Axis)
{
	// 割合補間で棒を一周させる
	float amount;
	if (m_ROTATE_ANGLE - m_RotatedAngle <= m_ROTATE_THRESHOLD)
	{
		m_IsEndRotate = true;
	}
	amount = (m_ROTATE_INTERPOLATION_ANGLE_REF - m_RotatedAngle) * m_ROTATE_INTERPOLATION_RATE;
	m_RotatedAngle += amount;

	GameObject* rodConnection = m_Manager->GetModelParts(PlayerManager::ModelPartsId::RodConnection);
	rodConnection->m_LocalRotation *= Math::AxisRotation_Degree(Axis, amount);
}

void PlayerAnimationState_Roll::PreEndRodRotate()
{
	// 現在の棒の位置から元の棒の位置まで割合補間で移動する
	D3DXVECTOR3 cameraForward = Manager::GetScene()->GetActiveCamera()->GetAttachObject()->GetForward();
	cameraForward = { cameraForward.x, 0.0f, cameraForward.z };
	cameraForward = Math::Normalize(cameraForward);

	GameObject* rodConnection = m_Manager->GetModelParts(PlayerManager::ModelPartsId::RodConnection);
	D3DXVECTOR3 rodForward = rodConnection->GetForward();
	rodForward = { rodForward.x, 0.0f, rodForward.z };
	rodForward = Math::Normalize(rodForward);

	D3DXVECTOR3 y = { 0.0f, 1.0f, 0.0f };
	D3DXVECTOR3 axis;
	D3DXQUATERNION q = Math::GetQuaternionIdentity();

	// 振り向きに使う回転軸を決定
	if (rodForward == -cameraForward)
	{// z軸と水平な場合
		// 外積の結果がおかしくなるので手動で指定
		axis = y;
	}
	else
	{// z軸と水平ではない場合
		// 外積を使うことで近い方から回れる回転軸を求められる
		D3DXVec3Cross(&axis, &rodForward, &cameraForward);
	}

	// 現在の向きと向きたい方向とのなす角を求める
	float angle = Math::VectorAngle(rodForward, cameraForward);
	if (angle > m_END_ROTATE_THRESHOLD)
	{
		angle *= m_END_ROTATE_INTERPOLATION_RATE;
	}
	else
	{
		m_IsEndRotate = true;
	}
	// 回転クオータニオンを作る
	q *= Math::AxisRotation_Radian(axis, angle);
	// 回転の反映
	rodConnection->m_LocalRotation *= q;
}

void PlayerAnimationState_Roll::MainScaleChange()
{
	// 棒のスケールを変化させる
	GameObject* obj = m_Manager->GetAttackCollision()->GetAttachObject()->GetParent();
	float amount = (1.0f - obj->m_LocalScale.x);

	if (amount > m_SCALE_INTERPOLATION_THRESHOLD)
	{
		amount *= m_SCALE_INTERPOLATION_RATE;
	}
	else
	{
		m_IsEndScaling = true;
	}

	obj->m_LocalScale += { amount, amount, amount };
}

void PlayerAnimationState_Roll::PreEndScaleChange()
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
