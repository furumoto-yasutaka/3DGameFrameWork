/*******************************************************************************
*
*	タイトル：	たまごエネミー接近ステートクラス	[ eggEnemyState_Approach.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyState_Approach.h"
#include "manager.h"
#include "gameObject.h"

EggEnemyState_Approach::EggEnemyState_Approach(EggEnemyManager* Manager)
	: EggEnemyStateBase(Manager, EggEnemyManager::AiStateId::Approach)
{
	m_CommonParam->m_MoveMagnitudeMax = m_MOVE_MAGNITUDE_MAX;
}

void EggEnemyState_Approach::Update()
{
	CheckDistance();
	UpdateAngle();
	UpdateMove();
	CheckNeedJump();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}

void EggEnemyState_Approach::LateUpdate()
{
	AddVelocity();
}

void EggEnemyState_Approach::CheckDistance()
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
	
	if (distanceSq > m_SEARCH_RANGE2 * m_SEARCH_RANGE2)
	{// 距離が遠くなった場合
		// 徘徊ステートに遷移
		m_Manager->RequestNextAiState((int)EggEnemyManager::AiStateId::Search);
	}
	else if (distanceSq <= m_ATTACK_START_RANGE2 * m_ATTACK_START_RANGE2)
	{// 距離が近い場合
		// 攻撃ステートに遷移
		m_Manager->RequestNextAiState((int)EggEnemyManager::AiStateId::Attack);
	}
}

void EggEnemyState_Approach::UpdateAngle()
{
	GameObject* player = Manager::GetScene()->GetGameObject("Player");
	D3DXVECTOR3 eggPos = m_Manager->GetAttachObject()->GetWorldPosition();
	D3DXVECTOR3 playerPos = player->GetWorldPosition();
	D3DXVECTOR3 distanceVec = playerPos - eggPos;
	distanceVec = { distanceVec.x, 0.0f, distanceVec.z };
	D3DXVECTOR3 distanceVecNormal = Math::Normalize(distanceVec);
	float distanceSq = D3DXVec3LengthSq(&distanceVec);

	if (distanceSq <= 0.0f)
	{// ベクトルが不正な場合
		// 徘徊ステートに遷移する
		m_Manager->RequestNextAiState((int)EggEnemyManager::AiStateId::Search);
	}
	else
	{// ベクトルが正常な場合
		// 移動方向を更新する
		m_CommonParam->m_MoveAngle = distanceVecNormal;
	}
}
