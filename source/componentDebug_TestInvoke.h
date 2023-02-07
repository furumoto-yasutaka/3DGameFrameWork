/*******************************************************************************
*
*	タイトル：	「TestInvoke」スクリプト情報保持クラス	[ componentDebug_TestInvoke.h ]
*
*	作成者：	古本 泰隆
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
