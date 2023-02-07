/*******************************************************************************
*
*	タイトル：	プレイヤー入力受付スクリプト	[ playerInputListener_MouseKeyboard.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerInputListener.h"

#include <optional>

class PlayerInputListener_MouseKeyboard : public PlayerInputListener
{
//public:
//	enum class InputWASD
//	{
//		W = (1 << 0),
//		A = (1 << 1),
//		S = (1 << 2),
//		D = (1 << 3),
//	};
//
//private:
//	static inline const float m_DOUBLE_PUSH_WAIT_TIME = 0.4f;
//
//	optional<float> m_DoublePushWaitTimeCount_Avoid[4];

public:
	PlayerInputListener_MouseKeyboard(PlayerManager* Manager) : PlayerInputListener(Manager) {}

//	void UpdateQueue() override;	// 削除予定のキューの削除と入力の取得を行う
//
//private:
//	void UpdateDoublePushWaitTime();

	// 入力取得
	float InputMove_Z() override;			// 移動入力(前後)
	float InputMove_X() override;			// 移動入力(左右)
	bool InputJump() override;				// ジャンプ入力
	bool InputAvoid() override;				// 回避入力
	optional<float> InputRoll_L() override;	// 中範囲回転入力
	optional<float> InputRoll_R() override;	// 中範囲回転入力
	bool InputKnock() override;				// 叩き入力(ダッシュ叩き・落下叩き含む)
	bool InputKnockChargeWait() override;	// ため叩き入力
	bool InputRodScaling() override;		// 棒拡縮入力
	bool InputRodOpen() override;			// 棒展開入力
};
