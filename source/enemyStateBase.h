/*******************************************************************************
*
*	タイトル：	エネミーステート基底クラス	[ enemyStateBase.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "eggEnemyManager.h"

class EnemyManager;
class EnemyCommonParameter;

class EnemyStateBase
{
protected:
	static inline const float m_VELOCITY_MAX_XZ = 1.0f;						// 最大移動速度(XZ)
	static inline const float m_VELOCITY_MAX_Y = 0.5f;						// 最大移動速度(Y)
	static inline const float m_MOVE_MAGNITUDE_INTERPOLATION_SPEED = 0.1f;	// 移動速度の目標値への補間速度
	static inline const float m_JUMP_MAGNITUDE = 0.2f;						// ジャンプ力
	static inline const float m_GRAVITY = 0.5f;								// 重力
	static inline const float m_ROTATE_INTERPOLATION_SPEED = 0.1f;

	EnemyManager* m_Manager = NULL;
	EnemyCommonParameter* m_CommonParam = NULL;

public:
	EnemyStateBase(EnemyManager* Manager)
		: m_Manager(Manager),
		m_CommonParam(Manager->GetCommonParameter())
	{}

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

protected:
	// エネミー制御系メソッド
	void UpdateMove();
	void CalcMoveSpeed();
	void CalcMoveVelocity();
	void CheckNeedJump();
	void AddGravity();			// 重力
	void CalcResistance();		// 抵抗
	void CorrectionVelocity();	// 加速度補正
	void RotateAngle();			// 向き補正

	void AddVelocity();			// 座標に加速度を反映

	void Jump();

public:
	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	virtual int GetStateId() = 0;
	/////////////////////////////
};