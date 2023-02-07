/*******************************************************************************
*
*	�^�C�g���F	��l�̎��_�J�����R���|�[�l���g	[ firstPersonCamera.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "firstPersonCamera.h"
#include "renderer.h"
#include "gameObject.h"
#include "manager.h"
#include "input.h"

void FirstPersonCamera::Init(bool IsActive,
	GameObject* FollowObject, D3DXVECTOR3 FollowOffset)
{
	Camera::Init(IsActive);
	m_FollowObject = FollowObject;
	m_FollowOffset = FollowOffset;
}

void FirstPersonCamera::Uninit()
{

}

void FirstPersonCamera::Update()
{
	//-----------------
	// ���_����
	//-----------------
	// ���͂��擾
	m_RotateXValue += Input::GetMouseMoveY() * m_RotateSenseY;
	m_RotateYValue += Input::GetMouseMoveX() * m_RotateSenseX;
	// ���̊p�x�Ő���
	if (m_RotateXValue > m_RotateMaxX) { m_RotateXValue = m_RotateMaxX; }
	else if (m_RotateXValue < -m_RotateMaxX) { m_RotateXValue = -m_RotateMaxX; }
	// ��]�𔽉f
	D3DXQuaternionIdentity(&m_AttachObject->m_LocalRotation);
	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_RotateYValue);
	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(m_AttachObject->GetRight(), m_RotateXValue);
}

void FirstPersonCamera::LateUpdate()
{
	SystemComponent::LateUpdate();

	//-----------------
	// �J�����Ǐ]
	//-----------------
	if (m_FollowObject)
	{
		D3DXVECTOR3 forward, up, right;
		forward = m_FollowObject->GetForward() * m_FollowOffset.z;
		up = m_FollowObject->GetUp() * m_FollowOffset.y;
		right = m_FollowObject->GetRight() * m_FollowOffset.x;

		m_AttachObject->m_LocalPosition = m_FollowObject->m_LocalPosition + forward + up + right;
	}

	Camera::LateUpdate();
}

void FirstPersonCamera::Draw()
{
	// �A�N�e�B�u��Ԃ̃J�����łȂ��ꍇ�͏I������
	if (Manager::GetScene()->GetActiveCamera() != this) { return; }

	// �r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 pos = m_AttachObject->m_LocalPosition;
	D3DXVECTOR3 target = m_AttachObject->m_LocalPosition + m_AttachObject->GetForward();
	D3DXMatrixLookAtLH(&m_ViewMatrix, &pos, &target, &up);
	Renderer::SetViewMatrix(&m_ViewMatrix);

	// �v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,
		(float)WINDOW_RESOLUTION_WIDTH / WINDOW_RESOLUTION_HEIGHT,
		0.1f, 1000.0f);
	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}
