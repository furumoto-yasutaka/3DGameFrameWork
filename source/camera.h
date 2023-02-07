/*******************************************************************************
*
*	�^�C�g���F	�J�����R���|�[�l���g	[ camera.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"

class Camera : public SystemComponent
{
protected:
	D3DXMATRIX m_ViewMatrix;	// �J�����̎p��
	D3DXMATRIX m_ProjectionMatrix;

public:
	Camera(GameObject* AttachObject) : SystemComponent(AttachObject) {}

	virtual void Init(bool IsActive);
	void Uninit() override {}
	void Update() override {}
	virtual void LateUpdate() override;
	void Draw() override;

	bool CheckFrustumCulling(D3DXVECTOR3 Position);

	virtual void SetStructuredBuffer();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	virtual D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	/////////////////////////////
};
