/*******************************************************************************
*
*	タイトル：	たまごエネミーステート基底クラス	[ eggEnemyStateBase.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "enemyStateBase.h"

class EggEnemyStateBase : public EnemyStateBase
{
protected:
	EggEnemyManager::AiStateId m_StateId;

public:
	EggEnemyStateBase(EggEnemyManager* Manager, EggEnemyManager::AiStateId StateId)
		: EnemyStateBase(Manager),
		m_StateId(StateId)
	{
		m_CommonParam->m_MoveMagnitudeMax = 0.0f;
	}

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	int GetStateId() override { return (int)m_StateId; }
	/////////////////////////////
};
