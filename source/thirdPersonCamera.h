/*******************************************************************************
*
*	�^�C�g���F	�O�l�̎��_�J�����R���|�[�l���g	[ thirdPersonCamera.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"
#include "camera.h"

class ThirdPersonCamera : public Camera
{
public:
	enum class InputModeId
	{
		Mouse = 0,
		Controller,
	};

private:
	InputModeId	m_InputMode = InputModeId::Mouse;
	GameObject* m_FollowObject = NULL;						// �ǔ��ΏۃI�u�W�F�N�g
	D3DXVECTOR3	m_FollowOffset;								// �ǔ����W�I�t�Z�b�g�l
	bool		m_IsRotateXReverse = false;					// X����]�̓��͔��]
	bool		m_IsRotateYReverse = false;					// Y����]�̓��͔��]
	D3DXVECTOR2	m_RotateSenseMouse = { 0.15f, 0.1f };		// ��]���x(�}�E�X)
	D3DXVECTOR2	m_RotateSenseController = { 2.0f, 1.0f };	// ��]���x(�R���g���[���[)
	float		m_RotateMaxX = 60.0f;						// ��]���(X)

	D3DXVECTOR2 m_RotateValue;				// ���[�J�������ւ̉�]��
	float		m_FollowSpeed = 0.4f;		// ��ԑ��x(0.0f < v <= 1.0f)

	D3DXMATRIX m_CameraMatrix;				// �J�����̎p��

public:
	D3DXVECTOR3 m_Offset;					// �O��������W�𑀍삷�邽�߂̃I�t�Z�b�g

public:
	ThirdPersonCamera(GameObject* AttachObject) : Camera(AttachObject) {}

	void Init(bool IsActive, InputModeId InputMode, GameObject* FollowObject = NULL,
		D3DXVECTOR3 FollowOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	void Uninit() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;

	D3DXVECTOR2 GetRotateInput();

	void SetStructuredBuffer() override;

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	float GetRotateYValue() { return m_RotateValue.y; }

	void SetFollowObject(GameObject* FollowObject) { m_FollowObject = FollowObject; }

	void SetFollowOffset(D3DXVECTOR3 FollowOffset) { m_FollowOffset = FollowOffset; }

	void SetRotateSenseMouseX(float SenseX) { m_RotateSenseMouse.x = SenseX; }

	void SetRotateSenseMouseY(float SenseY) { m_RotateSenseMouse.y = SenseY; }

	void SetRotateSenseControllerX(float SenseX) { m_RotateSenseController.x = SenseX; }

	void SetRotateSenseControllerY(float SenseY) { m_RotateSenseController.y = SenseY; }

	void SetRotateMaxX(float MaxX) { m_RotateMaxX = MaxX; }
	/////////////////////////////
};
