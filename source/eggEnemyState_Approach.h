/*******************************************************************************
*
*	タイトル：	たまごエネミー接近ステートクラス	[ eggEnemyState_Approach.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyStateBase.h"

class EggEnemyState_Approach : public EggEnemyStateBase
{
private:
	static inline const float m_MOVE_MAGNITUDE_MAX = 0.07f;
	static inline const D3DXVECTOR3 m_SEARCH_RANGE = { 12.0f, 10.0f, 20.0f };	// 探知範囲
	static inline const D3DXVECTOR3 m_ATTACK_START_RANGE = { 0.5f, 1.0f, 1.5f };
	//--------------------------------
	// 仮
	static inline const float m_SEARCH_RANGE2 = 20.0f;
	static inline const float m_ATTACK_START_RANGE2 = 1.5f;
	//--------------------------------

public:
	EggEnemyState_Approach(EggEnemyManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void CheckDistance();
	void UpdateAngle();
};
