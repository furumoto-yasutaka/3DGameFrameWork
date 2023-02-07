/*******************************************************************************
*
*	タイトル：	プレイヤー回避ステートクラス	[ playerActionState_Avoid.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerActionState_Avoid.h"
#include "camera.h"
#include "gameObject.h"
#include "collisionContactRecorder_PlayerGround.h"

PlayerActionState_Avoid::PlayerActionState_Avoid(PlayerManager* Manager)
	: PlayerActionStateBase(Manager, PlayerManager::ActionStateId::Avoid)
{
	m_CoolTimeCount = m_COOL_TIME;
	InitAvoid();
	if (!m_Param->m_IsExtend)
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None);
	}
	else
	{
		m_Manager->RequestNextAnimationState(PlayerManager::AnimationStateId::None_Extend);
	}
}

void PlayerActionState_Avoid::Update()
{
	UpdateCoolTime();
	CheckQueue(
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_Z].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Move_X].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::Jump].Tag |
		PlayerInputListener::m_ACTION_INFO[(int)PlayerInputListener::ActionId::RodOpen].Tag
	);

	UpdateAvoid();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}
void PlayerActionState_Avoid::LateUpdate()
{
	AddVelocity();
}

bool PlayerActionState_Avoid::CheckElemContinue(bool IsCanExec, int Id)
{
	if (PlayerActionStateBase::CheckElemContinue(IsCanExec, Id) ||
		m_CoolTimeCount)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerActionState_Avoid::ExecMove_Z(PlayerInputListener::ActionElement* Elem)
{
	SetMoveInput_Z(Elem->Value);
	SetCorrectionAngleZ(Elem->Value);
}
void PlayerActionState_Avoid::ExecMove_X(PlayerInputListener::ActionElement* Elem)
{
	SetMoveInput_X(Elem->Value);
	SetCorrectionAngleX(Elem->Value);
}
void PlayerActionState_Avoid::ExecJump(PlayerInputListener::ActionElement* Elem)
{
	m_Manager->RequestNextActionState(PlayerManager::ActionStateId::None);
	this->Jump();
}

void PlayerActionState_Avoid::InitAvoid()
{
	m_Param->m_Velocity = { 0.0f, 0.0f, 0.0f };

	if (!m_Manager->GetGroundCollision()->GetIsContact())
	{
		m_Param->m_IsCanAirAvoid = false;
	}

	PlayerInputListener* input = m_Manager->GetInputListener();

	D3DXVECTOR3 angle = { input->InputMove_X(), 0.0f, input->InputMove_Z() };
	GameObject* obj = Manager::GetScene()->GetActiveCamera()->GetAttachObject();
	D3DXVECTOR3 forward = obj->GetForward();
	forward = Math::Normalize(forward.x, 0.0f, forward.z);
	D3DXVECTOR3 right = obj->GetRight();
	right = Math::Normalize(right.x, 0.0f, right.z);

	if (D3DXVec3LengthSq(&angle) == 0.0f)
	{
		D3DXVECTOR3 back = -forward;
		m_TargetAngle = { back.x, 0.0f, back.z };
	}
	else
	{
		angle = Math::Normalize(angle);
		m_TargetAngle = forward * angle.z + right * angle.x;
	}
}

void PlayerActionState_Avoid::UpdateAvoid()
{
	float amount = (m_MOVE_SPEED_VALUE - m_MoveTotalAmount) * m_MOVE_SPEED_RATE;

	if (m_MoveTotalAmount + amount < m_MOVE_LENGTH - m_MOVE_THRESHOLD)
	{
		m_MoveTotalAmount += amount;
		m_Manager->GetAttachObject()->m_LocalPosition += m_TargetAngle * amount;
	}
	else
	{
		m_MoveTotalAmount = m_MOVE_LENGTH;
		m_Manager->GetAttachObject()->m_LocalPosition += m_TargetAngle * (m_MOVE_LENGTH - m_MoveTotalAmount);
		
		// 回避ステートを終了する
		m_Param->m_Velocity = m_TargetAngle * amount * 1.0f;
		m_Manager->RequestNextActionState(PlayerManager::ActionStateId::Dash);
		m_InputListener->SetActionCoolTime(PlayerInputListener::ActionId::Avoid, 0.2f);
	}
}

void PlayerActionState_Avoid::SetCorrectionAngleX(float Value)
{
	m_CorrectionAngleX = Value;

	if (m_CorrectionAngleZ)
	{
		CorrectionAvoidAngle();
	}
}

void PlayerActionState_Avoid::SetCorrectionAngleZ(float Value)
{
	m_CorrectionAngleZ = Value;

	if (m_CorrectionAngleX)
	{
		CorrectionAvoidAngle();
	}
}

void PlayerActionState_Avoid::CorrectionAvoidAngle()
{


	m_CorrectionAngleX.reset();
	m_CorrectionAngleZ.reset();
}
