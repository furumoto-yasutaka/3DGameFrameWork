/*******************************************************************************
*
*	タイトル：	プレイヤーアニメーションステート基底クラス	[ playerAnimationStateBase.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerManager.h"

class PlayerAnimationStateBase
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
		float CoverRotateTargetAngle = 0.0f;
		float CoverRotateAngle = 0.0f;
	};

protected:
	static inline const float m_CAMERA_FOLLOW_ROTATE_INTERPOLATION_RATE = 0.3f;

	static inline const float m_SPHERE_ROTATE_SPEED = 30.0f;				// 移動速度1あたりの玉の回転速度
	static inline const float m_COVER_ROTATE_ANGLE_MAX = 45.0f;				// カバーの最大角度
	static inline const float m_COVER_ROTATE_ANGLE_RATE = 60.0f;			// 移動速度1あたりのカバーの角度
	static inline const float m_COVER_ROTATE_INTERPOLATION_RATE = 0.3f;		// カバーの回転補間速度

	PlayerManager*					m_Manager = NULL;

	PlayerManager::AnimationStateId m_AnimationStateId;
	AnimationStepId					m_AnimationStepId = AnimationStepId::Main;
	bool							m_IsCameraRotate = true;	// カメラの回転を棒接続部分に無視させるか

	AnimationBaseParam m_AnimationBaseParam;

public:
	PlayerAnimationStateBase(
		PlayerManager* Manager, PlayerManager::AnimationStateId AnimationStateId, AnimationBaseParam Parameter)
		: m_Manager(Manager),
		m_AnimationStateId(AnimationStateId),
		m_AnimationBaseParam(Parameter)
	{}
	virtual ~PlayerAnimationStateBase() {}

	virtual void Update();
	virtual void LateUpdate();

	virtual void MainAnimation() = 0;
	virtual void PreEndAnimation() = 0;

	void PreEnd();	// アニメーションの終了アニメーションに遷移する
	void End();		// アニメーションの終了に遷移する

	void UpdateParentRotateLock();
	void UpdateCameraRotate();

	void UpdateSphereRotate(float MoveSpeed);	// 移動による球の回転
	void UpdateCoverRotate(float MoveSpeed);	// 移動によるカバーの傾け

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	PlayerManager::AnimationStateId GetStateId() { return m_AnimationStateId; }
	AnimationStepId GetAnimationStepId() { return m_AnimationStepId; }
	AnimationBaseParam GetAnimationBaseParam() { return m_AnimationBaseParam; }
	/////////////////////////////
};
