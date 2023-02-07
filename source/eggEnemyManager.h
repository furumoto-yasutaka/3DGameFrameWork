/*******************************************************************************
*
*	タイトル：	たまごエネミー統括スクリプト	[ eggEnemyManager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "enemyManager.h"

class EggEnemyManager : public EnemyManager
{
public:
	enum class AiStateId
	{
		Null = 0,		// 無し
		Search,			// 徘徊
		Approach,		// 接近
		Find,			// 発見
		Attack,			// 攻撃
		KnockBack,		// ノックバック
		Wince,			// ひるみ
		Stick,			// 引っ付き
		Death,			// 死亡
	};
	enum class AnimationStateId
	{
		Null = 0,
		None,
		Find,
		Approach,
		HeadAttack,
		KnockBack,
		Wince,
	};

private:
	static inline const float m_WINCE_VALUE_MAX = 3.0f;
	static inline const float m_ROLL_DISTANCE_RATE_STICK_THRESHOLD = 0.7f;

	AiStateId m_RecvAiStateId = AiStateId::Null;
	AiStateId m_NextAiStateId = AiStateId::Null;

	AnimationStateId m_NextAnimationStateId = AnimationStateId::Null;

public:
	EggEnemyManager(GameObject* AttachObject) : EnemyManager(AttachObject) {}

	void Init();
	void LateInit() override;
	void Uninit() override;
	void Update() override;
	void LateUpdate() override;

	void ChangeNextGeneralState() override;				// 汎用ステートの遷移処理
	void RequestNextAiState(int Next) override;			// AIステートの遷移リクエスト
	void ChangeNextAiState() override;					// AIステートの遷移処理
	void RequestNextAnimationState(int Next) override;	// アニメーションステートの遷移リクエスト
	void ChangeNextAnimationState() override;			// アニメーションステートの遷移処理

	void ShortRollDamage() override;
	void RollDamage(float DistanceRate) override;
	void LongRollDamage() override;

	void ChangeStickState();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	int GetRecvAiStateId() override { return (int)m_RecvAiStateId; }
	AnimationStateId GetNextAnimationStateId() { return m_NextAnimationStateId; }
	/////////////////////////////
};
