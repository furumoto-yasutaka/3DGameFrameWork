/*******************************************************************************
*
*	タイトル：	プレイヤー入力受付スクリプト	[ playerInputListener.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <list>
#include <optional>

class PlayerManager;

class PlayerInputListener
{
public:
	enum class ActionId
	{
		Move_Z = 0,
		Move_X,
		Jump,
		Avoid,
		Roll_Left,
		Roll_Right,
		KnockChargeWait,
		Knock,
		RodScaling,
		RodOpen,
		Length,
	};
	struct ActionElement
	{
		ActionId Id;
		float Value;
		float ValidTime;

		ActionElement(ActionId Id, float Value, float ValidTime)
		{
			this->Id = Id;
			this->Value = Value;
			this->ValidTime = ValidTime;
		}
	};
	struct ActionInfo
	{
		bool IsCanOverLap;
		int Tag;
	};
	// 各アクションの入力についての情報
	static inline const ActionInfo m_ACTION_INFO[(int)ActionId::Length] =
	{
		{ true,		(1 << (int)ActionId::Move_Z) },
		{ true,		(1 << (int)ActionId::Move_X) },
		{ true,		(1 << (int)ActionId::Jump) },
		{ false,	(1 << (int)ActionId::Avoid) },
		{ false,	(1 << (int)ActionId::Roll_Left) },
		{ false,	(1 << (int)ActionId::Roll_Right) },
		{ false,	(1 << (int)ActionId::KnockChargeWait) },
		{ false,	(1 << (int)ActionId::Knock) },
		{ false,	(1 << (int)ActionId::RodScaling) },
		{ true,		(1 << (int)ActionId::RodOpen) },
	};

private:
	static inline const float	m_VALID_TIME = 0.5f;		// 先行入力有効時間

	PlayerManager*				m_Manager = NULL;
	list<ActionElement*>		m_ActionQueue;				// 入力情報のキュー
	list<ActionElement*>		m_DeleteList;				// 削除する予定のキュー

	optional<float> m_ActionCoolTime[(int)ActionId::Length];

public:
	PlayerInputListener(PlayerManager* Manager) : m_Manager(Manager) {}

	virtual void UpdateQueue();	// 削除予定のキューの削除と入力の取得を行う
	void DeleteRequest(ActionElement* Elem);
	void SetActionCoolTime(ActionId Id, float Time);
	void ResetActionCoolTime(ActionId Id);
	void ResetActionCoolTimeAll();
	
	// 入力取得
	virtual float InputMove_Z() = 0;			// 移動入力(前後)
	virtual float InputMove_X() = 0;			// 移動入力(左右)
	virtual bool InputJump() = 0;				// ジャンプ入力
	virtual bool InputAvoid() = 0;				// 回避入力
	virtual optional<float> InputRoll_L() = 0;	// 中範囲回転入力
	virtual optional<float> InputRoll_R() = 0;	// 中範囲回転入力
	virtual bool InputKnock() = 0;				// 叩き入力(ダッシュ叩き・落下叩き含む)
	virtual bool InputKnockChargeWait() = 0;	// ため叩き入力
	virtual bool InputRodScaling() = 0;			// 棒拡縮入力
	virtual bool InputRodOpen() = 0;			// 棒展開入力

private:
	void CheckValidTime();	// 入力の有効時間を確認
	void DeleteElement();	// 有効時間切れの要素をキューから削除
	void UpdateCoolTime();	// 入力ごとのクールタイムを更新

	// キューに追加
	void SetMoveAction();				// 移動
	void SetJumpAction();				// ジャンプ
	void SetAvoidAction();				// 回避
	void SetRollAction();				// 中範囲回転
	void SetKnockAction();				// 叩き(ダッシュ叩き・落下叩き含む)
	void SetKnockChargeWaitAction();	// ため叩き
	void SetRodScalingAction();			// 棒拡縮
	void SetRodOpenAction();			// 棒展開

public:
	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	void SetManager(PlayerManager* Manager) { m_Manager = Manager; }

	list<ActionElement*> GetQueue() { return m_ActionQueue; }

	optional<float> GetActionCoolTime(int Id) { return m_ActionCoolTime[Id]; }
	/////////////////////////////
};
