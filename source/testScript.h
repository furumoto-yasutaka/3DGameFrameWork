/*******************************************************************************
*
*	�^�C�g���F	�e�X�g�p�R���|�[�l���g	[ testScript.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
