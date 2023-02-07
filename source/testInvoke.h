/*******************************************************************************
*
*	タイトル：	Invoke検証スクリプト	[ testInvoke.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class ComponentDebugInfo;
class ComponentDebug_TestInvoke;

class TestInvoke : public ScriptComponent
{
private:
	float m_Interval = 5.0f;
	float m_Speed = 0.01f;

#ifdef _DEBUG
	ComponentDebug_TestInvoke* m_ComponentDebug = NULL;
#endif

public:
	TestInvoke(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init();
	void Uninit() override { ScriptComponent::Uninit(); }
	void Update() override;
	void LateUpdate() override { ScriptComponent::LateUpdate(); }
	void Draw() override {}

	void Reset();

#ifdef _DEBUG
	float* GetIntervalPointer() { return &m_Interval; }
	float* GetSpeedPointer() { return &m_Speed; }

	ComponentDebugInfo* GetComponentDebugInfo() override;
#endif
};
