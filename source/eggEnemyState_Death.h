/*******************************************************************************
*
*	タイトル：	たまごエネミー死亡ステートクラス	[ eggEnemyState_Death.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyStateBase.h"

class EggEnemyState_Death : public EggEnemyStateBase
{
private:


public:
	EggEnemyState_Death(EggEnemyManager* Manager)
		: EggEnemyStateBase(Manager, EggEnemyManager::AiStateId::Death)
	{}

	void Update() override {}
	void LateUpdate() override {}
};
