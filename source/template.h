/*******************************************************************************
*
*	タイトル：	スクリプト	[ .h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class Template : public ScriptComponent
{
private:


public:
	Template(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init();
	void Uninit() override { ScriptComponent::Uninit(); }
	void Update() override;
	void LateUpdate() override { ScriptComponent::LateUpdate(); }
	void Draw() override {}
};
