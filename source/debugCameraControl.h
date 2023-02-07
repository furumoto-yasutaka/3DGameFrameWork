/*******************************************************************************
*
*	�^�C�g���F	�f�o�b�O�p�J��������X�N���v�g	[ debugCameraControl.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class DebugCameraControl : public ScriptComponent
{
private:
	float		m_RotateSenseX = 0.15f;	// ��]���x(X)
	float		m_RotateSenseY = 0.1f;	// ��]���x(Y)
	float		m_RotateMaxX = 60.0f;	// ��]���(X)
	float		m_MoveSpeed = 0.1f;		// �ړ����x

	float		m_RotateXValue = 0.0f;	// ���[�J��X�����ւ̉�]��
	float		m_RotateYValue = 0.0f;	// ���[�J��Y�����ւ̉�]��

public:
	DebugCameraControl(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init() {}
	void Uninit() override {}
	void Update() override;
	void Draw() override {}
};