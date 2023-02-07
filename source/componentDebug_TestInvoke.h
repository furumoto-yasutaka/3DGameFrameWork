/*******************************************************************************
*
*	�^�C�g���F	�uTestInvoke�v�X�N���v�g���ێ��N���X	[ componentDebug_TestInvoke.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "componentDebugInfo.h"
#include "testInvoke.h"

class ComponentDebug_TestInvoke : public ComponentDebugInfo
{
private:
	TestInvoke* m_Component = NULL;

public:
	ComponentDebug_TestInvoke(TestInvoke* Component)
		: ComponentDebugInfo(),
		m_Component(Component)
	{}

	void Draw() override
	{
		if (ImGui::TreeNode("TestInvokeScript"))
		{
			ImGui::SliderFloat("Interval", m_Component->GetIntervalPointer(), 0.1f, 10.0f);
			ImGui::SliderFloat("Speed", m_Component->GetSpeedPointer(), 0.001f, 0.1f);
		
			ImGui::TreePop();
		}
	}
};
