/*******************************************************************************
*
*	タイトル：	デバッグウィンドウ制御クラス	[ debugManager.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <list>

class DebugWindow;

class DebugManager
{
private:
	static inline const ImVec2 m_WINDOW_SIZE = { 300.0f, 300.0f };
	static inline const float m_LIST_WIDTH = 250.0f;
	static inline const float m_LIST_BLANK_HEIGHT = 12.0f;
	static inline const float m_LIST_LINE_HEIGHT = 23.0f;

	static inline list<DebugWindow*> m_WindowList;

public:
	static inline bool m_IsWireFrame = false;				// ワイヤーフレーム
	static inline bool m_IsParentLine = false;				// オブジェクトとの親子関係
	static inline bool m_IsCollisionFrame = true;			// 当たり判定のフレーム
	static inline bool m_IsSpaceDivisionFrame = false;		// 空間分割のフレーム

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();	// 各ウィンドウの表示制御用のウィンドウを作りたい

	static void DrawBegin();
	static void DrawEnd();

	static int AddWindow(DebugWindow* window)
	{
		if (find(m_WindowList.begin(), m_WindowList.end(), window) == m_WindowList.end())
		{
			m_WindowList.push_back(window);
			return size(m_WindowList) - 1;
		}

		return -1;
	}

	static void DeleteWindow(DebugWindow* window)
	{
		m_WindowList.remove(window);
	}
};
