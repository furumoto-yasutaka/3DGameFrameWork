/*******************************************************************************
*
*	�^�C�g���F	�V�[���ύX�E�B���h�E�N���X	[ debugWindow.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

		// ���W�Œ�ݒ�ŃE�B���h�E��\��
		ImGui::Begin(m_WindowName.c_str(), ((bool*)0), ImGuiWindowFlags_NoMove);

		if (ImGui::Button("Demo_Invoke"))
		{
			
		}

		ImGui::End();
	}
};
