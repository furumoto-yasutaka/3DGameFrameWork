/*******************************************************************************
*
*	タイトル：	プレイヤーメインステート基底クラス	[ playerActionStateBase.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "playerManager.h"
#include "playerInputListener.h"

class PlayerActionStateBase
{
protected:
	static inline const float		m_VELOCITY_MAX_XZ = 1.0f;						// 最大移動速度(XZ)
	static inline const float		m_VELOCITY_MAX_Y = 0.5f;						// 最大移動速度(Y)
	static inline const float		m_WALK_MAGNITUDE = 0.2f;						// 通常移動の最大速度
	static inline const float		m_MOVE_MAGNITUDE_INTERPOLATION_SPEED = 0.1f;	// 移動速度の目標値への補間速度
	static inline const float		m_TURN_SPEED = 0.2f;							// 振り向き速度
	static inline const float		m_JUMP_MAGNITUDE = 0.2f;						// ジャンプ力
	static inline const float		m_GRAVITY = 0.5f;								// 重力
	static inline const D3DXVECTOR3 m_RESISTANCE = { 0.9f, 0.999f, 0.9f };			// 抵抗係数
	static inline const float		m_ROTATE_INTERPOLATION_SPEED = 0.2f;			// オブジェクト方向補間速度

	PlayerManager* m_Manager = NULL;
	PlayerParameter* m_Param = NULL;
	PlayerInputListener* m_InputListener = NULL;
	PlayerManager::ActionStateId m_ActionStateId;

	optional<float> m_CoolTimeCount;	// 入力の受け付け待ち時間
	
	// 各入力に対する実行メソッド納めた配列
	void(PlayerActionStateBase::* m_ExecMethod[(int)PlayerInputListener::ActionId::Length])(PlayerInputListener::ActionElement* Elem) =
	{
		&PlayerActionStateBase::ExecMove_Z,
		&PlayerActionStateBase::ExecMove_X,
		&PlayerActionStateBase::ExecJump,
		&PlayerActionStateBase::ExecAvoid,
		&PlayerActionStateBase::ExecRoll_Left,
		&PlayerActionStateBase::ExecRoll_Right,
		&PlayerActionStateBase::ExecKnockChargeWait,
		&PlayerActionStateBase::ExecKnock,
		&PlayerActionStateBase::ExecRodScaling,
		&PlayerActionStateBase::ExecRodOpen,
	};

public:
	PlayerActionStateBase(PlayerManager* Manager, PlayerManager::ActionStateId ActionStateId)
		: m_Manager(Manager), 
		m_Param(Manager->GetParameter()),
		m_InputListener(Manager->GetInputListener()),
		m_ActionStateId(ActionStateId)
	{
		m_Param->m_MoveMagnitudeMax = m_WALK_MAGNITUDE;
		m_Param->m_TurnSpeed = m_TURN_SPEED;
		m_Param->m_JumpMagnitude = m_JUMP_MAGNITUDE;
	}

	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

protected:
	virtual void CheckQueue(int Tag);						// キューを確認して必要に応じて処理を行う
	virtual bool CheckElemContinue(bool IsCanExec, int Id);	// アクションを実行するかを判断
	void UpdateCoolTime();									// アクションごとのクールタイムを更新

	// 各入力実行メソッド
	virtual void ExecMove_Z(PlayerInputListener::ActionElement* Elem);
	virtual void ExecMove_X(PlayerInputListener::ActionElement* Elem);
	virtual void ExecJump(PlayerInputListener::ActionElement* Elem);
	virtual void ExecAvoid(PlayerInputListener::ActionElement* Elem);
	virtual void ExecRoll_Left(PlayerInputListener::ActionElement* Elem);
	virtual void ExecRoll_Right(PlayerInputListener::ActionElement* Elem);
	virtual void ExecKnockChargeWait(PlayerInputListener::ActionElement* Elem);
	virtual void ExecKnock(PlayerInputListener::ActionElement* Elem);
	virtual void ExecRodScaling(PlayerInputListener::ActionElement* Elem);
	virtual void ExecRodOpen(PlayerInputListener::ActionElement* Elem);

	// プレイヤー制御系メソッド
	void SetMoveInput_Z(float Value);
	void SetMoveInput_X(float Value);
	void UpdateMove();
	float CalcStickTilt(float InputLenSq);
	void CalcMoveSpeed(float TargetMagnitude);
	void CalcMoveVelocity();

	void Jump();

	void AddGravity();			// 重力
	void CalcResistance();		// 抵抗
	void CorrectionVelocity();	// 加速度補正
	void RotateAngle();			// 向き補正
	void AddVelocity();			// 座標に加速度を反映

public:
	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	PlayerManager::ActionStateId GetStateId() { return m_ActionStateId; }
	/////////////////////////////
};
