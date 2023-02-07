/*******************************************************************************
*
*	タイトル：	テスト用コンポーネント	[ testScript.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class TestScript : public ScriptComponent
{
private:
	bool a = false;
	float time = 0.0f;

public:
	TestScript(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init();
	void Uninit() override {}
	void Update() override;
	void Draw() override {}
};
