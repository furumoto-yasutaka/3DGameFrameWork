/*******************************************************************************
*
*	タイトル：	テスト用コンポーネント	[ testScript2.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class TestScript2 : public ScriptComponent
{
public:
	TestScript2(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init();
	void Uninit() override {}
	void Update() override;
	void Draw() override {}
};
