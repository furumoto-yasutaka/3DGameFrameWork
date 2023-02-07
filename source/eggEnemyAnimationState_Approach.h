/*******************************************************************************
*
*	�^�C�g���F	���܂��G�l�~�[�ǐՃA�j���[�V�����N���X	[ eggEnemyAnimationState_Approach.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "eggEnemyAnimationStateBase.h"

class EggEnemyAnimationState_Approach : public EggEnemyAnimationStateBase
{
public:
	EggEnemyAnimationState_Approach(EggEnemyManager* Manager, AnimationBaseParam Parameter)
		: EggEnemyAnimationStateBase(Manager, EggEnemyManager::AnimationStateId::Approach, Parameter)
	{}

	void MainAnimation() override;
	void PreEndAnimation() override;
};
