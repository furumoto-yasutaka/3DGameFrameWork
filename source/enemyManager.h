/*******************************************************************************
*
*	タイトル：	エネミー統括基底スクリプト	[ enemyManager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"
#include "aabbCollider3d.h"
#include "obbCollider3d.h"
#include "gameObject.h"

class EnemyStateBase;
class EnemyAnimationStateBase;
template<class T>
class CollisionContactRecorder;

class EnemyCommonParameter
{
public:
	// 現在地
	float			m_WinceValue = 0.0f;				// 怯み値
	D3DXVECTOR3		m_Velocity = { 0.0f, 0.0f, 0.0f };	// 加速度
	D3DXVECTOR3		m_MoveAngle = { 0.0f, 0.0f, 0.0f };	// 移動方向
	float			m_MoveMagnitude = 0.0f;				// 現在の移動速度(マグニチュード)
	float			m_MoveAngleDistance = 0.0f;			// オブジェクトの向きと移動方向との角度差
	float			m_NowFrameGravity = 0.0f;			// このフレームにかかっている重力
	D3DXVECTOR3		m_SearchRange = { 0.0f, 0.0f, 0.0f };	// 探知範囲

	// 最大値
	float			m_MoveMagnitudeMax = 0.0f;

	EnemyCommonParameter() {}
};

class EnemyManager : public ScriptComponent
{
public:
	enum class GeneralStateId
	{
		Idle = 0,
		Run,
		Float,
		Jump,
	};

protected:
	// ステート関係
	EnemyStateBase* m_AiState = NULL;
	EnemyAnimationStateBase* m_AnimationState = NULL;
	GeneralStateId m_GeneralStateId = GeneralStateId::Idle;	// 汎用ステートID

	EnemyCommonParameter* m_CommonParameter = NULL;

	// 連携コンポーネント
	CollisionContactRecorder<AABBCollider3D>* m_GroundCollision = NULL;
	CollisionContactRecorder<OBBCollider3D>* m_SearchCollision = NULL;
	CollisionContactRecorder<OBBCollider3D>* m_AttackCollision = NULL;
	CollisionContactRecorder<OBBCollider3D>* m_JumpCollision = NULL;

public:
	EnemyManager(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	virtual void LateInit() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	void Draw() override {}

	virtual void ChangeNextGeneralState() = 0;				// 汎用ステートの遷移処理
	virtual void RequestNextAiState(int Next) = 0;			// AIステートの遷移リクエスト
	virtual void ChangeNextAiState() = 0;					// AIステートの遷移処理
	virtual void RequestNextAnimationState(int Next) = 0;	// アニメーションステートの遷移リクエスト
	virtual void ChangeNextAnimationState() = 0;			// アニメーションステートの遷移処理

	virtual void ShortRollDamage() = 0;
	virtual void RollDamage(float DistanceRate) = 0;
	virtual void LongRollDamage() = 0;

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	GeneralStateId GetGeneralStateId() { return m_GeneralStateId; }
	virtual int GetRecvAiStateId() = 0;
	EnemyCommonParameter* GetCommonParameter() { return m_CommonParameter; }
	CollisionContactRecorder<AABBCollider3D>* GetGroundCollision() { return m_GroundCollision; }
	CollisionContactRecorder<OBBCollider3D>* GetSearchCollision() { return m_SearchCollision; }
	CollisionContactRecorder<OBBCollider3D>* GetAttackCollision() { return m_AttackCollision; }
	CollisionContactRecorder<OBBCollider3D>* GetJumpCollision() { return m_JumpCollision; }
	
	GameObject* GetModelRoot() { return m_AttachObject->GetChild(4); }
	/////////////////////////////
};
