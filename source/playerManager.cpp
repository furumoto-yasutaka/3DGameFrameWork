/*******************************************************************************
*
*	タイトル：	プレイヤー制御スクリプト	[ playerManager.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "playerManager.h"
#include "manager.h"
#include "camera.h"
#include "gameObject.h"
#include "math.h"
#include "collisionContactRecorder_PlayerGround.h"
#include "collisionContactRecorder_PlayerAttack.h"
#include "playerInputListener_Controller.h"
#include "playerInputListener_MouseKeyboard.h"
#include "playerHpManager.h"
#include "input.h"

// アクションステート用
#include "playerActionState_None.h"
#include "playerActionState_Dash.h"
#include "playerActionState_Turn.h"
#include "playerActionState_Avoid.h"
#include "playerActionState_ShortRoll_Left.h"
#include "playerActionState_ShortRoll_Right.h"
#include "playerActionState_Roll_Left.h"
#include "playerActionState_Roll_Right.h"
#include "playerActionState_LongRoll_Left.h"
#include "playerActionState_LongRoll_Right.h"
#include "playerActionState_Knock.h"
#include "playerActionState_DashKnock.h"
#include "playerActionState_ChargeKnock.h"
#include "playerActionState_DropKnock.h"
#include "playerActionState_RodScaling.h"
#include "playerActionState_RodOpen.h"

// アニメーションステート用
#include "playerAnimationState_None.h"
#include "playerAnimationState_None_Extend.h"
#include "playerAnimationState_ShortRoll_Left.h"
#include "playerAnimationState_ShortRoll_Right.h"
#include "playerAnimationState_Roll_Left.h"
#include "playerAnimationState_Roll_Right.h"
#include "playerAnimationState_RodScaling_Extend.h"
#include "playerAnimationState_RodScaling_Put.h"

void PlayerManager::Init(InputModeId InputMode)
{
	m_Parameter = new PlayerParameter();
	m_AnimationState = new PlayerAnimationState_None(this,
		PlayerAnimationStateBase::AnimationBaseParam(0.0f, 0.0f));

	switch (InputMode)
	{
		using enum InputModeId;
	case MouseKeyboard:
		m_InputListener = new PlayerInputListener_MouseKeyboard(this);
		break;
	case Controller:
		m_InputListener = new PlayerInputListener_Controller(this);
		break;
	}
}

void PlayerManager::LateInit()
{
	GameObject* rod = m_AttachObject->GetChild(1)->GetChild(1)->GetChild(0)->GetChild(0)->GetChild(0);
	m_StickEnemyList = rod->GetChild(2);

	m_GroundCollision = m_AttachObject->GetChild(0)->GetComponent<CollisionContactRecorder_PlayerGround<AABBCollider3D>>();
	m_AttackCollision = rod->GetComponent<CollisionContactRecorder_PlayerAttack<OBBCollider3D>>();

	m_ModelParts[(int)ModelPartsId::Sphere] = m_AttachObject->GetChild(1)->GetChild(0);
	m_ModelParts[(int)ModelPartsId::Cover] = m_AttachObject->GetChild(1)->GetChild(1);
	m_ModelParts[(int)ModelPartsId::RodConnection] = m_ModelParts[(int)ModelPartsId::Cover]->GetChild(0);
	m_ModelParts[(int)ModelPartsId::RodCenter] = m_ModelParts[(int)ModelPartsId::RodConnection]->GetChild(0);
	m_ModelParts[(int)ModelPartsId::Rod] = m_ModelParts[(int)ModelPartsId::RodCenter]->GetChild(0);
	m_ModelParts[(int)ModelPartsId::RodFirstHalf] = m_ModelParts[(int)ModelPartsId::Rod]->GetChild(0);
	m_ModelParts[(int)ModelPartsId::RodLetterHalf] = m_ModelParts[(int)ModelPartsId::Rod]->GetChild(1);
	m_ModelParts[(int)ModelPartsId::RodLetterHalf_Left] = m_ModelParts[(int)ModelPartsId::RodLetterHalf]->GetChild(0);
	m_ModelParts[(int)ModelPartsId::RodLetterHalf_Right] = m_ModelParts[(int)ModelPartsId::RodLetterHalf]->GetChild(1);

	m_ActionState = new PlayerActionState_None(this);
	m_NextActionStateId = m_ActionState->GetStateId();

	m_AttachObject->GetComponent<AABBCollider3D>()->SetVelocityRef(&m_Parameter->m_Velocity, 0.0f);

	GameObject* obj = Manager::GetScene()->GetGameObject(m_PLAYER_HP_MANAGER_OBJ_NAME);
	obj->GetComponent<PlayerHpManager>()->CreateUi(m_Parameter);
}

void PlayerManager::Uninit()
{
	delete m_AnimationState;
	delete m_ActionState;
	delete m_Parameter;
	delete m_InputListener;
}

void PlayerManager::Update()
{
	// 入力をキューに記録
	m_InputListener->UpdateQueue();

	// キューを確認してステートに応じた処理を実行
	m_ActionState->Update();

	m_AnimationState->Update();

#ifdef _DEBUG
	//if (Input::GetKeyboardTrigger(DIK_1))
	//{
	//	m_Parameter->m_Hp--;
	//}
	//if (Input::GetKeyboardTrigger(DIK_2))
	//{
	//	m_Parameter->m_Hp++;
	//}

	//printf("%d                 \n", m_Parameter->m_Hp);

	//// アクションステートを表示
	//printf("ActionState : ");
	//switch (m_NextActionStateId)
	//{
	//	using enum ActionStateId;
	//case None:				printf("None                   \n\n");	break;
	//case Dash:				printf("Dash                   \n\n");	break;
	//case Turn:				printf("Turn                   \n\n");	break;
	//case Avoid:				printf("Avoid                  \n\n");	break;
	//case ShortRoll_Left:	printf("ShortRoll_Left         \n\n");	break;
	//case ShortRoll_Right:	printf("ShortRoll_Right        \n\n");	break;
	//case Roll_Left:			printf("Roll_Left              \n\n");	break;
	//case Roll_Right:		printf("Roll_Right             \n\n");	break;
	//case LongRoll_Left:		printf("LongRoll_Left          \n\n");	break;
	//case LongRoll_Right:	printf("LongRoll_Right         \n\n");	break;
	//case Knock:				printf("Knock                  \n\n");	break;
	//case DashKnock:			printf("DashKnock              \n\n");	break;
	//case ChargeKnock:		printf("ChargeKnock            \n\n");	break;
	//case DropKnock:			printf("DropKnock              \n\n");	break;
	//case RodScaling:		printf("RodScaling             \n\n");	break;
	//case RodOpen:			printf("RodOpen                \n\n");	break;
	//default: return;
	//}

	//switch (m_AnimationState->GetStateId())
	//{
	//	using enum AnimationStateId;
	//case None:				printf("None                   \n");	break;
	//case None_Extend:		printf("None_Extend            \n");	break;
	//case ShortRoll_Left:	printf("ShortRoll_Left         \n");	break;
	//case ShortRoll_Right:	printf("ShortRoll_Right        \n");	break;
	//case Roll_Left:			printf("Roll_Left              \n");	break;
	//case Roll_Right:		printf("Roll_Right             \n");	break;
	//case RodScaling_Extend:	printf("RodScaling_Extend      \n");	break;
	//case RodScaling_Put:	printf("RodScaling_Put         \n");	break;
	//default: return;
	//}
#endif
}

void PlayerManager::LateUpdate()
{
	ScriptComponent::LateUpdate();

	m_ActionState->LateUpdate();
	m_AnimationState->LateUpdate();

	// ステート更新
	ChangeNextGeneralState();
	ChangeNextActionState();
	ChangeNextAnimationState();
}

void PlayerManager::ChangeNextGeneralState()
{
	D3DXVECTOR3 v = m_Parameter->m_Velocity;
	float nowFrameGravity = m_Parameter->m_NowFrameGravity;

	if (m_GroundCollision->GetIsContact())
	{// 接地している
		if (D3DXVec3LengthSq(&v) <= nowFrameGravity * nowFrameGravity)
		{// 動いていない
			m_GeneralStateId = GeneralStateId::Idle;
		}
		else
		{// 動いている
			m_GeneralStateId = GeneralStateId::Run;
		}
	}
	else
	{// 接地していない
		if (v.y > 0.0f)
		{// 上昇している
			m_GeneralStateId = GeneralStateId::Jump;
		}
		else
		{// 降下しているor動きなし
			m_GeneralStateId = GeneralStateId::Float;
		}
	}
}

void PlayerManager::RequestNextActionState(ActionStateId Next)
{
	m_NextActionStateId = Next;
}

void PlayerManager::ChangeNextActionState()
{
	if (m_NextActionStateId == ActionStateId::Null)
	{
		return;
	}

	PlayerActionStateBase* temp = NULL;

	switch (m_NextActionStateId)
	{
		using enum ActionStateId;
	case None:				temp = new PlayerActionState_None(this);			break;
	case Dash:				temp = new PlayerActionState_Dash(this);			break;
	case Turn:				temp = new PlayerActionState_Turn(this);			break;
	case Avoid:				temp = new PlayerActionState_Avoid(this);			break;
	case ShortRoll_Left:	temp = new PlayerActionState_ShortRoll_Left(this);	break;
	case ShortRoll_Right:	temp = new PlayerActionState_ShortRoll_Right(this);	break;
	case Roll_Left:			temp = new PlayerActionState_Roll_Left(this);		break;
	case Roll_Right:		temp = new PlayerActionState_Roll_Right(this);		break;
	case LongRoll_Left:		temp = new PlayerActionState_LongRoll_Left(this);	break;
	case LongRoll_Right:	temp = new PlayerActionState_LongRoll_Right(this);	break;
	case Knock:				temp = new PlayerActionState_Knock(this);			break;
	case DashKnock:			temp = new PlayerActionState_DashKnock(this);		break;
	case ChargeKnock:		temp = new PlayerActionState_ChargeKnock(this);		break;
	case DropKnock:			temp = new PlayerActionState_DropKnock(this);		break;
	case RodScaling:		temp = new PlayerActionState_RodScaling(this);		break;
	case RodOpen:			temp = new PlayerActionState_RodOpen(this);			break;
	}

	if (temp)
	{
		m_RecvActionStateId = m_ActionState->GetStateId();
		delete m_ActionState;
		m_ActionState = temp;
	}

	m_NextActionStateId = ActionStateId::Null;
}

void PlayerManager::RequestNextAnimationState(AnimationStateId Next)
{
	m_NextAnimationState = Next;
	m_AnimationState->PreEnd();
}

void PlayerManager::ChangeNextAnimationState()
{
	if (m_NextAnimationState == AnimationStateId::Null ||
		m_AnimationState->GetAnimationStepId() != PlayerAnimationStateBase::AnimationStepId::End)
	{
		return;
	}

	PlayerAnimationStateBase::AnimationBaseParam param = m_AnimationState->GetAnimationBaseParam();

	PlayerAnimationStateBase* temp = NULL;

	switch (m_NextAnimationState)
	{
		using enum AnimationStateId;
	case None:				temp = new PlayerAnimationState_None(this, param);					break;
	case None_Extend:		temp = new PlayerAnimationState_None_Extend(this, param);			break;
	case ShortRoll_Left:	temp = new PlayerAnimationState_ShortRoll_Left(this, param);		break;
	case ShortRoll_Right:	temp = new PlayerAnimationState_ShortRoll_Right(this, param);		break;
	case Roll_Left:			temp = new PlayerAnimationState_Roll_Left(this, param);				break;
	case Roll_Right:		temp = new PlayerAnimationState_Roll_Right(this, param);			break;
	case RodScaling_Extend:	temp = new PlayerAnimationState_RodScaling_Extend(this, param);		break;
	case RodScaling_Put:	temp = new PlayerAnimationState_RodScaling_Put(this, param);		break;
	}

	if (temp)
	{
		delete m_AnimationState;
		m_AnimationState = temp;
	}

	m_NextAnimationState = AnimationStateId::Null;
}

void PlayerManager::Damage(int Value)
{
	// 無敵状態でない場合ダメージを与える
	if (m_Parameter->m_InvincibleTime <= 0.0f)
	{
		m_Parameter->m_Hp -= Value;

		if (m_Parameter->m_Hp < 0)
		{
			m_Parameter->m_Hp = 0;
		}

		m_Parameter->m_InvincibleTime = 2.0f;
	}
}
