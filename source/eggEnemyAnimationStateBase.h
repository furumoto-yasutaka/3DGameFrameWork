/*******************************************************************************
*
*	タイトル：	たまごエネミーアニメーション基底クラス	[ eggEnemyAnimationStateBase.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "enemyAnimationStateBase.h"
#include "eggEnemyManager.h"

class EggEnemyAnimationStateBase : public EnemyAnimationStateBase
{
protected:
	EggEnemyManager* m_Manager;

	EggEnemyManager::AnimationStateId m_AnimationStateId;

public:
	EggEnemyAnimationStateBase(
		EggEnemyManager* Manager, EggEnemyManager::AnimationStateId AnimationStateId, AnimationBaseParam Parameter)
		: EnemyAnimationStateBase(Manager, Parameter),
		m_Manager(Manager),
		m_AnimationStateId(AnimationStateId)
	{}

	virtual void Update() override
	{
		EnemyAnimationStateBase::Update();
	}
	virtual void LateUpdate() override
	{
		EnemyAnimationStateBase::LateUpdate();
	}

	virtual void MainAnimation() = 0;
	virtual void PreEndAnimation() = 0;

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	EggEnemyManager::AnimationStateId GetStateId() { return m_AnimationStateId; }
	/////////////////////////////
};
