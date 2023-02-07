/*******************************************************************************
*
*	タイトル：	たまごエネミー攻撃ステートクラス	[ eggEnemyState_HeadAttack.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "eggEnemyState_HeadAttack.h"

EggEnemyState_HeadAttack::EggEnemyState_HeadAttack(EggEnemyManager* Manager)
	: EggEnemyStateBase(Manager, EggEnemyManager::AiStateId::Attack)
{
	// 攻撃用の当たり判定を有効にする
}

void EggEnemyState_HeadAttack::Update()
{
	UpdateMove();
	AddGravity();
	CalcResistance();
	CorrectionVelocity();
	RotateAngle();
}

void EggEnemyState_HeadAttack::LateUpdate()
{
	AddVelocity();
}

void EggEnemyState_HeadAttack::Attack()
{
	// オブジェクトに設定されている当たり判定と
	// 現在衝突しているオブジェクトを確認し、
	// プレイヤーが含まれていたらダメージを与える
}
