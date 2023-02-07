/*******************************************************************************
*
*	タイトル：　時間管理用静的クラス	[ time.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "time.h"

void Time::Init()
{
	// 初期化
	m_DeltaTimeMsec = 0;
	m_PlayTimeMsec = 0;
	m_SystemTimeMsec = timeGetTime();
}

void Time::Update()
{
	// 各変数を更新
	DWORD prevTime = m_SystemTimeMsec;
	m_SystemTimeMsec = timeGetTime();
	m_DeltaTimeMsec = m_SystemTimeMsec - prevTime;
	m_PlayTimeMsec += m_DeltaTimeMsec;

	// ミリ秒から秒に変換
	m_DeltaTimeSec = m_DeltaTimeMsec * 0.001f;
	m_PlayTimeSec = m_PlayTimeMsec * 0.001f;
	m_SystemTimeSec = m_SystemTimeMsec * 0.001f;
}
