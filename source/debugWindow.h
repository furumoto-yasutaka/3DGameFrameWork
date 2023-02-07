/*******************************************************************************
*
*	タイトル：	デバッグウィンドウ制御クラス	[ debugWindow.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "debugManager.h"

class DebugWindow
{
protected:
	int m_WindowId;					// ウィンドウID
	string m_WindowName;			// ウィンドウ名
	bool m_IsActive;				// ウィンドウが起動しているか
	ImVec2 m_WindowSize;			// ウィンドウサイズ
	D3DXVECTOR4 m_WindowClearColor;	// ウィンドウの色

public:
	DebugWindow(string Name, bool IsActive = true)
	{
		// ウィンドウを登録してIDを受け取る
		m_WindowId = DebugManager::AddWindow(this);

		m_WindowName = Name;
		m_IsActive = IsActive;
		m_WindowSize = ImVec2(200.0f, 300.0f);
		m_WindowClearColor = D3DXVECTOR4(0.45f, 0.55f, 0.60f, 1.00f);
	}
	~DebugWindow()
	{
		DebugManager::DeleteWindow(this);
	}

	virtual void Draw() = 0;

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	string GetName() { return m_WindowName; }

	bool GetIsActive() { return m_IsActive; }
	void SetIsActive(bool IsActive) { m_IsActive = IsActive; }
	/////////////////////////////
};
