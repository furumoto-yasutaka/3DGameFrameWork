/*******************************************************************************
*
*	タイトル：	たまごエネミー無しアニメーションクラス	[ eggEnemyAnimationState_None.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "eggEnemyAnimationStateBase.h"

class EggEnemyAnimationState_None : public EggEnemyAnimationStateBase
{
public:
	EggEnemyAnimationState_None(EggEnemyManager* Manager, AnimationBaseParam Parameter)
		: EggEnemyAnimationStateBase(Manager, EggEnemyManager::AnimationStateId::None, Parameter)
	{}

	void MainAnimation() override;
	void PreEndAnimation() override;
};
