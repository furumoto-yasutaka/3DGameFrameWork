/*******************************************************************************
*
*	タイトル：	プレイヤー入力受付スクリプト	[ playerInputListener_Controller.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "playerInputListener.h"

class PlayerInputListener_Controller : public PlayerInputListener
{
public:
	PlayerInputListener_Controller(PlayerManager* Manager) : PlayerInputListener(Manager) {}

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
