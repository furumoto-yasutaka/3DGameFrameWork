/*******************************************************************************
*
*	タイトル：	デバッグ画面用静的クラス	[ debugConsole.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "debugConsole.h"

void DebugConsole::Init()
{
	// コンソ―ルウィンドウ作成
	AllocConsole();

	// 書き込み準備
	m_Out = 0;
	(void)freopen_s(&m_Out, "CON", "w", stdout);

	// ハンドル取得
	m_Console = GetStdHandle(STD_OUTPUT_HANDLE);

	// カーソル座標初期化
	m_CursorPos.X = 0;
	m_CursorPos.Y = 0;
}
void DebugConsole::Uninit()
{
	// コンソール解放
	fclose(m_Out);
	FreeConsole();
}
void DebugConsole::Update()
{
	// カーソルを左上に移動
	SetConsoleCursorPosition(m_Console, m_CursorPos);
}
