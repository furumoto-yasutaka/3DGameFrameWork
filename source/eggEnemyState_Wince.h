/*******************************************************************************
*
*	タイトル：	たまごエネミーひるみステートクラス	[ eggEnemyState_Wince.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyStateBase.h"

class EggEnemyState_Wince : public EggEnemyStateBase
{
private:
	static inline const float m_WINCE_TIME = 7.0f;

	float m_TimeLimit = m_WINCE_TIME;

public:
	EggEnemyState_Wince(EggEnemyManager* Manager)
		: EggEnemyStateBase(Manager, EggEnemyManager::AiStateId::Wince)
	{}

	void Update() override;
	void LateUpdate() override;
};
