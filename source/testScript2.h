/*******************************************************************************
*
*	�^�C�g���F	�e�X�g�p�R���|�[�l���g	[ testScript2.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
