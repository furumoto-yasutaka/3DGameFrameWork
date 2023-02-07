/*******************************************************************************
*
*	タイトル：　時間管理用静的クラス	[ time.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

class Time
{
private:
	static inline float m_DeltaTimeSec;		// フレーム間経過時間(秒)
	static inline DWORD m_DeltaTimeMsec;	// フレーム間経過時間(ミリ秒)
	static inline float m_PlayTimeSec;		// 起動から現在までの時間(秒)
	static inline DWORD m_PlayTimeMsec;		// 起動から現在までの時間(ミリ秒)
	static inline float m_SystemTimeSec;	// システム内時刻(秒)
	static inline DWORD m_SystemTimeMsec;	// システム内時刻(ミリ秒)

public:
	static void Init();
	static void Uninit() {}
	static void Update();
	
	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	static float GetDeltaTimeSec() { return m_DeltaTimeSec; }
	static DWORD GetDeltaTimeMsec() { return m_DeltaTimeMsec; }

	static float GetPlayTimeSec() { return m_PlayTimeSec; }
	static DWORD GetPlayTimeMsec() { return m_PlayTimeMsec; }

	static float GetSystemTimeSec() { return m_SystemTimeSec; }
	static DWORD GetSystemTimeMsec() { return m_SystemTimeMsec; }
	/////////////////////////////
};
