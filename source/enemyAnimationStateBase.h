/*******************************************************************************
*
*	タイトル：	エネミーアニメーションステート基底クラス	[ enemyAnimationStateBase.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

class EnemyManager;

class EnemyAnimationStateBase
{
public:
	enum class AnimationStepId
	{
		Main = 0,
		PreEnd,
		End,
	};
	struct AnimationBaseParam
	{
		bool IsBodyRotate;
		float RotateTargetAngle;
		float RotateAngle;
	};

protected:
	static inline const float m_ROTATE_ANGLE_MAX = 45.0f;			// の最大角度
	static inline const float m_ROTATE_ANGLE_RATE = 1000.0f;			// 移動速度1あたりのの角度
	static inline const float m_ROTATE_INTERPOLATION_RATE = 0.3f;	// の回転補間速度

	EnemyManager* m_BaseManager = NULL;

	AnimationStepId	m_AnimationStepId = AnimationStepId::Main;

	AnimationBaseParam m_AnimationBaseParam;

public:
	EnemyAnimationStateBase(EnemyManager* Manager, AnimationBaseParam Parameter)
		: m_BaseManager(Manager),
		m_AnimationBaseParam(Parameter)
	{}
	virtual ~EnemyAnimationStateBase() {}

	virtual void Update();
	virtual void LateUpdate();

	virtual void MainAnimation() = 0;
	virtual void PreEndAnimation() = 0;

	virtual void PreEnd();	// アニメーションの終了アニメーションに遷移する
	virtual void End();		// アニメーションの終了に遷移する

	void UpdateBodyRotate(float MoveSpeed);	// 移動によるカバーの傾け

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	AnimationStepId GetAnimationStepId() { return m_AnimationStepId; }
	AnimationBaseParam GetAnimationBaseParam() { return m_AnimationBaseParam; }
	/////////////////////////////
};
