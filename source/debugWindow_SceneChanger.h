/*******************************************************************************
*
*	タイトル：	シーン変更ウィンドウクラス	[ debugWindow.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "debugWindow.h"

#include <list>
#include <string>

class DebugWindow_SceneChanger : public DebugWindow
{
public:
	DebugWindow_SceneChanger(string Name, bool IsActive = true)
		: DebugWindow(Name, IsActive) {}

	void Draw() override
	{
		ImGui::SetNextWindowSize(m_WindowSize, ImGuiCond_Once);

		// 座標固定設定でウィンドウを表示
		ImGui::Begin(m_WindowName.c_str(), ((bool*)0), ImGuiWindowFlags_NoMove);

		if (ImGui::Button("Demo_Invoke"))
		{
			
		}

		ImGui::End();
	}
};
