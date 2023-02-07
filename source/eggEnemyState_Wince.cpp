/*******************************************************************************
*
*	タイトル：	たまごエネミーひるみステートクラス	[ eggEnemyState_Wince.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyState_Wince.h"

void EggEnemyState_Wince::Update()
{
	if (m_TimeLimit <= 0.0f)
	{
		m_Manager->RequestNextAiState((int)EggEnemyManager::AiStateId::Search);
	}
	else
	{
		m_TimeLimit -= Time::GetDeltaTimeSec();
	}

	AddGravity();
	CalcResistance();
	CorrectionVelocity();
}

void EggEnemyState_Wince::LateUpdate()
{
	AddVelocity();
}
