/*******************************************************************************
*
*	�^�C�g���F	��l�̎��_�J�����R���|�[�l���g	[ firstPersonCamera.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"
#include "camera.h"

class FirstPersonCamera : public Camera
{
private:
	GameObject* m_FollowObject = NULL;	// �ǔ��ΏۃI�u�W�F�N�g
	D3DXVECTOR3	m_FollowOffset;			// �ǔ����W�I�t�Z�b�g�l
	float		m_RotateSenseX = 0.15f;	// ��]���x(X)
	float		m_RotateSenseY = 0.1f;	// ��]���x(Y)
	float		m_RotateMaxX = 60.0f;	// ��]���(X)

	float		m_RotateXValue = 0.0f;	// ���[�J��X�����ւ̉�]��
	float		m_RotateYValue = 0.0f;	// ���[�J��Y�����ւ̉�]��

public:
	FirstPersonCamera(GameObject* AttachObject) : Camera(AttachObject) {}

	void Init(bool IsActive,
		GameObject* FollowObject = NULL,
		D3DXVECTOR3 FollowOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	void Uninit() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
};
