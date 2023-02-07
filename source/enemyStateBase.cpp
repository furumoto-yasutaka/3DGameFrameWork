/*******************************************************************************
*
*	タイトル：	エネミーステート基底クラス	[ enemyStateBase.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "enemyStateBase.h"
#include "enemyManager.h"
#include "gameObject.h"
#include "collisionContactRecorder.h"

void EnemyStateBase::UpdateMove()
{
	// スピードを更新
	CalcMoveSpeed();

	// 加速度を決定
	CalcMoveVelocity();
}

void EnemyStateBase::CalcMoveSpeed()
{
	D3DXVECTOR3 notYVel = { m_CommonParam->m_Velocity.x, 0.0f, m_CommonParam->m_Velocity.z };
	float mag = D3DXVec3Length(&notYVel);

	// 当たり判定や諸々の影響で実際の速度が低下してしまった場合は移動速度を修正する
	if (mag < m_CommonParam->m_MoveMagnitude)
	{
		m_CommonParam->m_MoveMagnitude = mag;
	}

	// 速度を目標値に向けて補正
	m_CommonParam->m_MoveMagnitude +=
		(m_CommonParam->m_MoveMagnitudeMax - m_CommonParam->m_MoveMagnitude) * m_MOVE_MAGNITUDE_INTERPOLATION_SPEED;
}

void EnemyStateBase::CalcMoveVelocity()
{
	D3DXVECTOR3 forward = m_Manager->GetAttachObject()->GetForward();
	forward = Math::Normalize(forward.x, 0.0f, forward.z);
	D3DXVECTOR3 vel = Math::Normalize(forward) * m_CommonParam->m_MoveMagnitude;
	vel.y = m_CommonParam->m_Velocity.y;

	m_CommonParam->m_Velocity = vel;
}

void EnemyStateBase::CheckNeedJump()
{
	// 地面を移動中かつ壁が接近している場合ジャンプする
	if (m_Manager->GetGeneralStateId() == EggEnemyManager::GeneralStateId::Run &&
		m_Manager->GetJumpCollision()->GetIsContact())
	{
		Jump();
	}
}

void EnemyStateBase::AddGravity()
{
	m_CommonParam->m_NowFrameGravity = m_GRAVITY * Time::GetDeltaTimeSec();
	m_CommonParam->m_Velocity.y -= m_CommonParam->m_NowFrameGravity;
}

void EnemyStateBase::CalcResistance()
{
	// 抵抗を計算
	//m_CommonParam->m_Velocity.x *= m_CommonParam->m_RESISTANCE.x;
	//m_CommonParam->m_Velocity.y *= m_CommonParam->m_RESISTANCE.y;
	//m_CommonParam->m_Velocity.z *= m_CommonParam->m_RESISTANCE.z;
}

void EnemyStateBase::CorrectionVelocity()
{
	// 速度の補正(XZ)
	D3DXVECTOR3 tempVel = { m_CommonParam->m_Velocity.x, 0.0f, m_CommonParam->m_Velocity.z };
	float len = D3DXVec3LengthSq(&tempVel);
	if (len > m_VELOCITY_MAX_XZ * m_VELOCITY_MAX_XZ)
	{
		float y = m_CommonParam->m_Velocity.y;
		m_CommonParam->m_Velocity = Math::Normalize(tempVel) * m_VELOCITY_MAX_XZ;
		m_CommonParam->m_Velocity.y = y;
	}

	// 速度の補正(Y)
	if (m_CommonParam->m_Velocity.y > m_VELOCITY_MAX_Y)
	{
		m_CommonParam->m_Velocity.y = m_VELOCITY_MAX_Y;
	}
	else if (m_CommonParam->m_Velocity.y < -m_VELOCITY_MAX_Y)
	{
		m_CommonParam->m_Velocity.y = -m_VELOCITY_MAX_Y;
	}
}

void EnemyStateBase::RotateAngle()
{
	D3DXVECTOR3 notYMoveVel = m_CommonParam->m_MoveAngle;

	// 動きがない場合は補正しない
	if (D3DXVec3LengthSq(&notYMoveVel) <= FLT_EPSILON)
	{
		return;
	}


	D3DXVECTOR3 eggForward = m_Manager->GetAttachObject()->GetForward();
	eggForward = { eggForward.x, 0.0f, eggForward.z };
	eggForward = Math::Normalize(eggForward);

	D3DXQUATERNION q = Math::GetQuaternionIdentity();
	D3DXVECTOR3 normalNotY = Math::Normalize(notYMoveVel);
	D3DXVECTOR3 y = { 0.0f, 1.0f, 0.0f };
	D3DXVECTOR3 axis;

	// 振り向きに使う回転軸を決定
	if (normalNotY == -eggForward)
	{// z軸と水平な場合
		// 外積の結果がおかしくなるので手動で指定
		axis = y;
	}
	else
	{// z軸と水平ではない場合
		// 外積を使うことで近い方から回れる回転軸を求められる
		D3DXVec3Cross(&axis, &eggForward, &normalNotY);
	}

	// 現在の向きと向きたい方向とのなす角を求める
	m_CommonParam->m_MoveAngleDistance = Math::VectorAngle(normalNotY, eggForward);
	float angle = m_CommonParam->m_MoveAngleDistance * m_ROTATE_INTERPOLATION_SPEED;
	// 回転クオータニオンを作る
	q *= Math::AxisRotation_Radian(axis, angle);
	// 回転の反映
	m_Manager->GetAttachObject()->m_LocalRotation *= q;
}

void EnemyStateBase::AddVelocity()
{
	m_Manager->GetAttachObject()->m_LocalPosition += m_CommonParam->m_Velocity;
}

void EnemyStateBase::Jump()
{
	m_CommonParam->m_Velocity.y = m_JUMP_MAGNITUDE;
}
