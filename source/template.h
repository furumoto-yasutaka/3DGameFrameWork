/*******************************************************************************
*
*	�^�C�g���F	�X�N���v�g	[ .h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
