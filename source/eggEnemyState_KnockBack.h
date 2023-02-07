/*******************************************************************************
*
*	タイトル：	たまごエネミーノックバックステートクラス	[ eggEnemyState_KnockBack.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyStateBase.h"

class EggEnemyState_KnockBack : public EggEnemyStateBase
{
private:
	static inline const float m_KNOCKBACK_MAGNITUDE = 0.4f;

public:
	EggEnemyState_KnockBack(EggEnemyManager* Manager);

	void Update() override;
	void LateUpdate() override;
};
