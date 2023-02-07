/*******************************************************************************
*
*	タイトル：	画像点滅スクリプト	[ blinkImage.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class BlinkImage : public ScriptComponent
{
public:
	// 点滅方法
	enum class BlinkMode
	{
		None = 0,
		Fade,
	};
	// 点滅の進行状況
	enum class BlinkState
	{
		Visible = 0,
		ChangeInVisible,
		InVisible,
		ChangeVisible,
	};

private:
	BlinkMode	m_Mode;								// 点滅方法
	BlinkState	m_State;							// 点滅の進行状況
	float		m_TimeCountSec = 0.0f;				// 時間計測(秒)
	float		m_VisibleTimeSec = 0.0f;			// 表示の継続時間
	float		m_InVisibleTimeSec = 0.0f;			// 非表示の継続時間
	
	float		m_ChangeVisibleTimeSec = 0.0f;		// 表示にかける時間
	float		m_ChangeInVisibleTimeSec = 0.0f;	// 非表示にかける時間

public:
	BlinkImage(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init(BlinkMode Mode, float VisibleTimeSec, float InVisibleTimeSec,
			float ChangeVisibleTimeSec = 0.0f, float ChangeInVisibleTimeSec = 0.0f);
	void Uninit() override {}
	void Update() override;
	void Draw() override {}

private:
	// 透明度変更
	void ChangeAlpha();
	// 透明度変更(フェードモード)
	void ChangeAlpha_Fade();

	// 点滅状況変更
	void ChangeState();
	// 点滅状況変更(無設定モード)
	void ChangeState_None();
	// 点滅状況変更(フェードモード)
	void ChangeState_Fade();
};
