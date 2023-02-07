/*******************************************************************************
*
*	タイトル：	たまごエネミー徘徊ステートクラス	[ eggEnemyState_Search.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyState_Search.h"
#include "manager.h"
#include "gameObject.h"

EggEnemyState_Search::EggEnemyState_Search(EggEnemyManager* Manager)
	: EggEnemyStateBase(Manager, EggEnemyManager::AiStateId::Search)
{
	m_CommonParam->m_MoveMagnitudeMax = 0.0f;

	ChangeWait();

	m_Manager->RequestNextAnimationState((int)EggEnemyManager::AnimationStateId::None);
}

void EggEnemyState_Search::Update()
{
	m_StepTimeLimit -= Time::GetDeltaTimeSec();
	if (m_StepTimeLimit <= 0.0f)
	{
		ChangeStep();
	}

	Search();
	UpdateMove();
	CheckNeedJump();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}

void EggEnemyState_Search::LateUpdate()
{
	AddVelocity();
}

void EggEnemyState_Search::Search()
{
	// 視界にプレイヤーが存在するか判断
	// プレイヤーが探知用ボックスの範囲に入ったら見つけたとする
	

	// プレイヤーとの間に障害物があるか判断
	// レイをプレイヤーの中央に向けて発射する


	//----------------------------
	// とりあえず仮ではプレイヤーと一定の距離以下になったら見つけたとする
	GameObject* player = Manager::GetScene()->GetGameObject("Player");
	D3DXVECTOR3 eggPos = m_Manager->GetAttachObject()->GetWorldPosition();
	D3DXVECTOR3 playerPos = player->GetWorldPosition();
	D3DXVECTOR3 distanceVec = playerPos - eggPos;
	float distanceSq = D3DXVec3LengthSq(&distanceVec);

	if (distanceSq <= m_SEARCH_RANGE2 * m_SEARCH_RANGE2)
	{// 見つけた場合
		// 発見ステートに遷移
		m_Manager->RequestNextAiState((int)EggEnemyManager::AiStateId::Find);
	}
}

void EggEnemyState_Search::ChangeStep()
{
	float num;

	switch (m_SearchStepId)
	{
		using enum EggEnemyState_Search::SearchStepId;
	case Wait:
		// 移動を選択
		ChangeMove();
		break;
	case Move:
		if (m_MoveConsecutiveCount < m_MOVE_CONSECUTIVE_NUM)
		{
			num = Math::Random(1.0f);
			if (num <= m_MOVE_SELECT_RATE)
			{// 移動を選択
				ChangeMove();
			}
			else
			{// 待機を選択
				ChangeWait();
			}
		}
		else
		{// 待機を選択
			ChangeWait();
		}
		break;
	default:
		break;
	}
}

void EggEnemyState_Search::ChangeWait()
{
	m_SearchStepId = EggEnemyState_Search::SearchStepId::Wait;
	m_StepTimeLimit = m_WAIT_TIME_MIN + Math::Random(m_WAIT_TIME_MAX - m_WAIT_TIME_MIN);
	m_MoveConsecutiveCount = 0;
	m_CommonParam->m_MoveMagnitudeMax = 0.0f;
}

void EggEnemyState_Search::ChangeMove()
{
	m_SearchStepId = EggEnemyState_Search::SearchStepId::Move;
	m_StepTimeLimit = m_MOVE_TIME_MIN + Math::Random(m_MOVE_TIME_MAX - m_MOVE_TIME_MIN);
	m_MoveConsecutiveCount++;
	m_CommonParam->m_MoveAngle = CreateAngle();
	m_CommonParam->m_MoveMagnitudeMax = m_MOVE_MAGNITUDE_MAX;
}

D3DXVECTOR3 EggEnemyState_Search::CreateAngle()
{
	float x = 1.0f - Math::Random(2.0f);
	float z = 1.0f - Math::Random(2.0f);
	return Math::Normalize(x, 0.0f, z);
}
