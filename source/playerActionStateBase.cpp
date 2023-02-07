/*******************************************************************************
*
*	タイトル：	プレイヤーメインステート基底クラス	[ playerActionStateBase.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionStateBase.h"
#include "collisionContactRecorder_PlayerGround.h"
#include "gameObject.h"
#include "camera.h"

void PlayerActionStateBase::CheckQueue(int Tag)
{
	bool isCanExec = true;

	// キューを確認して処理を実行する
	for (PlayerInputListener::ActionElement* elem : m_InputListener->GetQueue())
	{
		int id = (int)elem->Id;

		if (!CheckElemContinue(isCanExec, id) &&
			Tag & PlayerInputListener::m_ACTION_INFO[id].Tag)
		{
			if (isCanExec)
			{
				isCanExec = PlayerInputListener::m_ACTION_INFO[id].IsCanOverLap;
			}

			// 入力に応じた処理を実行
			(this->*m_ExecMethod[id])(elem);
			// 入力を受理したので要素は削除
			m_InputListener->DeleteRequest(elem);
		}
	}
}
bool PlayerActionStateBase::CheckElemContinue(bool IsCanExec, int Id)
{
	// 既に同時受理不可の入力を受理した かつ 同時受理不可
	// または
	// 該当のアクションのクールタイムが残っている場合
	if ((!IsCanExec && !PlayerInputListener::m_ACTION_INFO[Id].IsCanOverLap) ||
		m_InputListener->GetActionCoolTime(Id))
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PlayerActionStateBase::UpdateCoolTime()
{
	if (m_CoolTimeCount)
	{
		m_CoolTimeCount.value() -= Time::GetDeltaTimeSec();
		if (m_CoolTimeCount <= 0.0f)
		{
			m_CoolTimeCount.reset();
		}
	}
}

/*******************************************************************************
*	各入力実行メソッド
*******************************************************************************/
void PlayerActionStateBase::ExecMove_Z(PlayerInputListener::ActionElement* Elem)
{
	SetMoveInput_Z(Elem->Value);
}
void PlayerActionStateBase::ExecMove_X(PlayerInputListener::ActionElement* Elem)
{
	SetMoveInput_X(Elem->Value);
}
void PlayerActionStateBase::ExecJump(PlayerInputListener::ActionElement* Elem)
{
	Jump();
}
void PlayerActionStateBase::ExecAvoid(PlayerInputListener::ActionElement* Elem)
{
	if (m_Manager->GetGroundCollision()->GetIsContact() ||
		m_Param->m_IsCanAirAvoid)
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Avoid);
	}
}
void PlayerActionStateBase::ExecRoll_Left(PlayerInputListener::ActionElement* Elem)
{
	if (m_Manager->GetParameter()->m_IsExtend)
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Roll_Left);
	}
	else
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::ShortRoll_Left);
	}
}
void PlayerActionStateBase::ExecRoll_Right(PlayerInputListener::ActionElement* Elem)
{
	if (m_Manager->GetParameter()->m_IsExtend)
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Roll_Right);
	}
	else
	{
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::ShortRoll_Right);
	}
}
void PlayerActionStateBase::ExecKnockChargeWait(PlayerInputListener::ActionElement* Elem)
{
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::KnockChargeWait);
}
void PlayerActionStateBase::ExecKnock(PlayerInputListener::ActionElement* Elem)
{
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Knock);
}
void PlayerActionStateBase::ExecRodScaling(PlayerInputListener::ActionElement* Elem)
{
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::RodScaling);
}
void PlayerActionStateBase::ExecRodOpen(PlayerInputListener::ActionElement* Elem)
{
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::RodOpen);
}

/*******************************************************************************
*	プレイヤー制御系メソッド
*******************************************************************************/
void PlayerActionStateBase::SetMoveInput_Z(float Value)
{
	m_Param->m_MoveInput.z = Value;
}
void PlayerActionStateBase::SetMoveInput_X(float Value)
{
	m_Param->m_MoveInput.x = Value;
}
void PlayerActionStateBase::UpdateMove()
{
	float lenSq = D3DXVec3LengthSq(&m_Param->m_MoveInput);
	float targetMoveMagnitude;

	if (lenSq != 0.0f)
	{// 入力あり
		// スティックの傾きを計算
		float tilt = CalcStickTilt(lenSq);
		targetMoveMagnitude = tilt * m_Param->m_MoveMagnitudeMax;
	}
	else
	{// 入力なし
		targetMoveMagnitude = 0.0f;
	}

	// スピードを更新
	CalcMoveSpeed(targetMoveMagnitude);

	// 加速度を決定
	CalcMoveVelocity();
}
float PlayerActionStateBase::CalcStickTilt(float InputLenSq)
{
	//------------------------------------------------
	// スティックの傾きを均一になるよう正規化して速度を求める
	//------------------------------------------------
	float angle, halfPi, rate;
	// ベクトルの角度を求める
	angle = atan2f(m_Param->m_MoveInput.z, m_Param->m_MoveInput.x);
	// 90度(ラジアン)で割ったあまりを求める
	halfPi = Math::m_PI * 0.5f;
	while (angle > halfPi) { angle -= halfPi; }
	// ベクトルの倍率を求める(角度が斜め(45度)であるほど値が大きくなる)
	rate = fabs(sinf(angle * 2)) + 1.0f;
	// 正しい傾きを求める
	return InputLenSq / rate;
}
void PlayerActionStateBase::CalcMoveSpeed(float TargetMagnitude)
{
	D3DXVECTOR3 notYVel = { m_Param->m_Velocity.x, 0.0f, m_Param->m_Velocity.z };
	float mag = D3DXVec3Length(&notYVel);

	// 当たり判定や諸々の影響で実際の速度が低下してしまった場合は移動速度を修正する
	if (mag < m_Param->m_MoveMagnitude)
	{
		m_Param->m_MoveMagnitude = mag;
	}

	// 速度を目標値に向けて補正
	m_Param->m_MoveMagnitude += (TargetMagnitude - m_Param->m_MoveMagnitude) * m_MOVE_MAGNITUDE_INTERPOLATION_SPEED;
}
void PlayerActionStateBase::CalcMoveVelocity()
{
	D3DXVECTOR3 forward = m_Manager->GetAttachObject()->GetForward();
	forward = Math::Normalize(forward.x, 0.0f, forward.z);
	D3DXVECTOR3 vel = Math::Normalize(forward) * m_Param->m_MoveMagnitude;
	vel.y = m_Param->m_Velocity.y;

	m_Param->m_Velocity = vel;
}

void PlayerActionStateBase::Jump()
{
	m_Param->m_Velocity.y = m_Param->m_JumpMagnitude;
}

void PlayerActionStateBase::AddGravity()
{
	m_Param->m_NowFrameGravity = m_GRAVITY * Time::GetDeltaTimeSec();
	m_Param->m_Velocity.y -= m_Param->m_NowFrameGravity;
}
void PlayerActionStateBase::CalcResistance()
{
	// 抵抗を計算
	//m_Param->m_Velocity.x *= m_Param->m_RESISTANCE.x;
	//m_Param->m_Velocity.y *= m_Param->m_RESISTANCE.y;
	//m_Param->m_Velocity.z *= m_Param->m_RESISTANCE.z;
}
void PlayerActionStateBase::CorrectionVelocity()
{
	// 速度の補正(XZ)
	D3DXVECTOR3 tempVel = { m_Param->m_Velocity.x, 0.0f, m_Param->m_Velocity.z };
	float len = D3DXVec3LengthSq(&tempVel);
	if (len > m_VELOCITY_MAX_XZ * m_VELOCITY_MAX_XZ)
	{
		float y = m_Param->m_Velocity.y;
		m_Param->m_Velocity = Math::Normalize(tempVel) * m_VELOCITY_MAX_XZ;
		m_Param->m_Velocity.y = y;
	}

	// 速度の補正(Y)
	if (m_Param->m_Velocity.y > m_VELOCITY_MAX_Y)
	{
		m_Param->m_Velocity.y = m_VELOCITY_MAX_Y;
	}
	else if (m_Param->m_Velocity.y < -m_VELOCITY_MAX_Y)
	{
		m_Param->m_Velocity.y = -m_VELOCITY_MAX_Y;
	}
}
void PlayerActionStateBase::RotateAngle()
{
	GameObject* obj = Manager::GetScene()->GetActiveCamera()->GetAttachObject();
	D3DXVECTOR3 cameraForward = obj->GetForward();
	D3DXVECTOR3 cameraRight = obj->GetRight();
	cameraForward = { cameraForward.x, 0.0f, cameraForward.z };
	cameraRight = { cameraRight.x, 0.0f, cameraRight.z };
	D3DXVECTOR3 notYVel = cameraForward * m_Param->m_MoveInput.z + cameraRight * m_Param->m_MoveInput.x;

	// 入力がない場合は補正しない
	if (D3DXVec3LengthSq(&notYVel) <= FLT_EPSILON)
	{
		m_Param->m_NowFrameRotateAngle = Math::GetQuaternionIdentity();
		return;
	}

	D3DXVECTOR3 playerForward = m_Manager->GetAttachObject()->GetForward();
	playerForward = { playerForward.x, 0.0f, playerForward.z };
	playerForward = Math::Normalize(playerForward);
	D3DXQUATERNION q = Math::GetQuaternionIdentity();
	D3DXVECTOR3 normalNotY = Math::Normalize(notYVel);
	D3DXVECTOR3 y = { 0.0f, 1.0f, 0.0f };
	D3DXVECTOR3 axis;

	// 振り向きに使う回転軸を決定
	if (normalNotY == -playerForward)
	{// z軸と水平な場合
		// 外積の結果がおかしくなるので手動で指定
		axis = y;
	}
	else
	{// z軸と水平ではない場合
		// 外積を使うことで近い方から回れる回転軸を求められる
		D3DXVec3Cross(&axis, &playerForward, &normalNotY);
	}

	// 現在の向きと向きたい方向とのなす角を求める
	m_Param->m_MoveAngleDistance = Math::VectorAngle(normalNotY, playerForward);
	float angle = m_Param->m_MoveAngleDistance * m_ROTATE_INTERPOLATION_SPEED;
	// 回転クオータニオンを作る
	q *= Math::AxisRotation_Radian(axis, angle);
	m_Param->m_NowFrameRotateAngle = q;
	// 回転の反映
	m_Manager->GetAttachObject()->m_LocalRotation *= q;
}
void PlayerActionStateBase::AddVelocity()
{
	m_Manager->GetAttachObject()->m_LocalPosition += m_Param->m_Velocity;
}
