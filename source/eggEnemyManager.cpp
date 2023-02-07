/*******************************************************************************
*
*	タイトル：	たまごエネミー統括スクリプト	[ eggEnemyManager.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyManager.h"
#include "gameObject.h"
#include "collisionContactRecorder.h"
#include "playerManager.h"

// Aiステート用
#include "eggEnemyState_Search.h"
#include "eggEnemyState_Approach.h"
#include "eggEnemyState_Find.h"
#include "eggEnemyState_HeadAttack.h"
#include "eggEnemyState_KnockBack.h"
#include "eggEnemyState_Wince.h"
#include "eggEnemyState_Stick.h"
#include "eggEnemyState_Death.h"

// アニメーションステート用
#include "eggEnemyAnimationState_None.h"
#include "eggEnemyAnimationState_Find.h"
#include "eggEnemyAnimationState_Approach.h"
#include "eggEnemyAnimationState_HeadAttack.h"
#include "eggEnemyAnimationState_KnockBack.h"
#include "eggEnemyAnimationState_Wince.h"

void EggEnemyManager::Init()
{
	m_CommonParameter = new EnemyCommonParameter();
	m_AnimationState = new EggEnemyAnimationState_None(this,
		EnemyAnimationStateBase::AnimationBaseParam(true, 0.0f, 0.0f));
}

void EggEnemyManager::LateInit()
{
	m_GroundCollision = m_AttachObject->GetChild(0)->GetComponent<CollisionContactRecorder<AABBCollider3D>>();
	m_SearchCollision = m_AttachObject->GetChild(1)->GetComponent<CollisionContactRecorder<OBBCollider3D>>();
	m_AttackCollision = m_AttachObject->GetChild(2)->GetComponent<CollisionContactRecorder<OBBCollider3D>>();
	m_JumpCollision = m_AttachObject->GetChild(3)->GetComponent<CollisionContactRecorder<OBBCollider3D>>();

	m_AiState = new EggEnemyState_Search(this);

	m_AttachObject->GetComponent<AABBCollider3D>()->SetVelocityRef(&m_CommonParameter->m_Velocity, 0.0f);
}

void EggEnemyManager::Uninit()
{
	delete m_CommonParameter;
	delete m_AiState;
	delete m_AnimationState;
}

void EggEnemyManager::Update()
{
	m_AiState->Update();
	m_AnimationState->Update();

	printf("%f                     \n", m_CommonParameter->m_WinceValue);

#ifdef _DEBUG
	switch ((AiStateId)m_AiState->GetStateId())
	{
		using enum AiStateId;
	case Search:		printf("Search              \n");	break;
	case Approach:		printf("Approach            \n");	break;
	case Find:			printf("Find                \n");	break;
	case Attack:		printf("Attack              \n");	break;
	case KnockBack:		printf("KnockBack           \n");	break;
	case Wince:			printf("Wince               \n");	break;
	case Stick:			printf("Stick               \n");	break;
	case Death:			printf("Death               \n");	break;
	default: break;
	}
#endif
}

void EggEnemyManager::LateUpdate()
{
	ScriptComponent::LateUpdate();

	m_AiState->LateUpdate();
	m_AnimationState->LateUpdate();

	ChangeNextGeneralState();
	ChangeNextAiState();
	ChangeNextAnimationState();
}

void EggEnemyManager::ChangeNextGeneralState()
{
	D3DXVECTOR3 v = m_CommonParameter->m_Velocity;
	float nowFrameGravity = m_CommonParameter->m_NowFrameGravity;

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

void EggEnemyManager::RequestNextAiState(int Next)
{
	m_NextAiStateId = (AiStateId)Next;
}

void EggEnemyManager::ChangeNextAiState()
{
	if ((AiStateId)m_AiState->GetStateId() == m_NextAiStateId)
	{
		return;
	}

	EggEnemyStateBase* temp = NULL;

	switch (m_NextAiStateId)
	{
		using enum AiStateId;
	case Search:	temp = new EggEnemyState_Search(this);		break;
	case Approach:	temp = new EggEnemyState_Approach(this);	break;
	case Find:		temp = new EggEnemyState_Find(this);		break;
	case Attack:	temp = new EggEnemyState_HeadAttack(this);	break;
	case KnockBack:	temp = new EggEnemyState_KnockBack(this);	break;
	case Wince:		temp = new EggEnemyState_Wince(this);		break;
	case Stick:		temp = new EggEnemyState_Stick(this);		break;
	case Death:		temp = new EggEnemyState_Death(this);		break;
	default: break;
	}

	if (temp)
	{
		m_RecvAiStateId = (AiStateId)m_AiState->GetStateId();
		delete m_AiState;
		m_AiState = temp;
	}
}

void EggEnemyManager::RequestNextAnimationState(int Next)
{
	m_NextAnimationStateId = (AnimationStateId)Next;
}

void EggEnemyManager::ChangeNextAnimationState()
{
	if (m_AnimationState->GetAnimationStepId() == EnemyAnimationStateBase::AnimationStepId::End)
	{
		return;
	}

	EnemyAnimationStateBase::AnimationBaseParam param = m_AnimationState->GetAnimationBaseParam();

	EnemyAnimationStateBase* temp = NULL;

	switch (m_NextAnimationStateId)
	{
		using enum AnimationStateId;
	case None:			temp = new EggEnemyAnimationState_None(this, param);		break;
	case Find:			temp = new EggEnemyAnimationState_Find(this, param);		break;
	case Approach:		temp = new EggEnemyAnimationState_Approach(this, param);	break;
	case HeadAttack:	temp = new EggEnemyAnimationState_HeadAttack(this, param);	break;
	case KnockBack:		temp = new EggEnemyAnimationState_KnockBack(this, param);	break;
	case Wince:			temp = new EggEnemyAnimationState_Wince(this, param);		break;
	default: break;
	}

	if (temp)
	{
		delete m_AnimationState;
		m_AnimationState = temp;
	}
}

void EggEnemyManager::ShortRollDamage()
{
	if (m_AiState->GetStateId() == (int)AiStateId::Wince)
	{
		ChangeStickState();
	}
	else
	{
		m_CommonParameter->m_WinceValue += 1.0f;

		if (m_CommonParameter->m_WinceValue >= m_WINCE_VALUE_MAX)
		{
			m_CommonParameter->m_WinceValue = 0.0f;
			RequestNextAiState((int)AiStateId::Wince);
		}
		else
		{
			RequestNextAiState((int)AiStateId::KnockBack);
		}
	}
}

void EggEnemyManager::RollDamage(float DistanceRate)
{
	if (m_AiState->GetStateId() == (int)AiStateId::Wince)
	{
		ChangeStickState();
	}
	else
	{
		if (DistanceRate >= m_ROLL_DISTANCE_RATE_STICK_THRESHOLD)
		{
			ChangeStickState();
		}
		else
		{
			m_CommonParameter->m_WinceValue += 1.0f + 2.0f * DistanceRate;
			if (m_CommonParameter->m_WinceValue >= m_WINCE_VALUE_MAX)
			{
				m_CommonParameter->m_WinceValue = 0.0f;
				RequestNextAiState((int)AiStateId::Wince);
			}
			else
			{
				RequestNextAiState((int)AiStateId::KnockBack);
			}
		}
	}
}

void EggEnemyManager::LongRollDamage()
{

}

void EggEnemyManager::ChangeStickState()
{
	RequestNextAiState((int)AiStateId::Stick);

	GameObject* stickEnemyList = Manager::GetScene()->GetGameObject("Player")->GetComponent<PlayerManager>()->GetStickEnemyList();
	m_AttachObject->SetParent(stickEnemyList, 0, (int)GameObject::SetParentOption::KeepPos);
	m_AttachObject->m_LocalPosition.x = 0.0f;

	m_AttachObject->GetComponent<AABBCollider3D>()->SetActive(false);
}
