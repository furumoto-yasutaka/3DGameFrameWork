/*******************************************************************************
*
*	�^�C�g���F	���܂��G�l�~�[�U���X�e�[�g�N���X	[ eggEnemyState_HeadAttack.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "eggEnemyStateBase.h"

class EggEnemyState_HeadAttack : public EggEnemyStateBase
{
private:

public:
	EggEnemyState_HeadAttack(EggEnemyManager* Manager);

	void Update() override;
	void LateUpdate() override;

	void Attack();	// �U���̓����蔻����m�F����
};