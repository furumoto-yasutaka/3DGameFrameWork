/*******************************************************************************
*
*	タイトル：	デバッグ画面用静的クラス	[ debugConsole.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

class DebugConsole
{
private:
	static inline FILE*		m_Out;
	static inline HANDLE	m_Console;		// コンソールハンドル
	static inline COORD		m_CursorPos;	// カーソル座標

public:
	static void Init();
	static void Uninit();
	static void Update();
};
