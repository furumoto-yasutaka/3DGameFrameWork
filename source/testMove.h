/*******************************************************************************
*
*	�^�C�g���F	�f���p�I�u�W�F�N�g�ړ��X�N���v�g	[ testMove.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class TestMove : public ScriptComponent
{
private:
	D3DXVECTOR3 m_FirstPos;
	D3DXVECTOR3 m_MoveRange;
	float m_Time = 0.0f;

public:
	TestMove(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init(D3DXVECTOR3 MoveRange);
	void Uninit() override { ScriptComponent::Uninit(); }
	void Update() override;
	void LateUpdate() override { ScriptComponent::LateUpdate(); }
	void Draw() override {}
};
