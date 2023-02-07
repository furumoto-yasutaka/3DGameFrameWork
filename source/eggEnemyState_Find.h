/*******************************************************************************
*
*	タイトル：	たまごエネミー発見ステートクラス	[ eggEnemyState_Find.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyStateBase.h"

class EggEnemyState_Find : public EggEnemyStateBase
{
private:
	static inline const float m_WAIT_TIME = 2.0f;
	static inline const D3DXVECTOR3 m_SEARCH_RANGE = { 12.0f, 10.0f, 20.0f };	// 探知範囲
	//--------------------------------
	// 仮
	static inline const float m_SEARCH_RANGE2 = 20.0f;
	//--------------------------------

	float m_WaitTimeLimit = m_WAIT_TIME;

public:
	EggEnemyState_Find(EggEnemyManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void CheckDistance();
	void UpdateAngle();
};
