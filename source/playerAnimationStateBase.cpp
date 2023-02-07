/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�A�j���[�V�����X�e�[�g���N���X	[ playerAnimationStateBase.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "playerAnimationStateBase.h"
#include "playerManager.h"
#include "gameObject.h"
#include "camera.h"

void PlayerAnimationStateBase::Update()
{
	switch (m_AnimationStepId)
	{
		using enum AnimationStepId;
	case Main:
		MainAnimation();
		break;
	case PreEnd:
		PreEndAnimation();
		break;
	default: break;
	}

	UpdateParentRotateLock();
	if (m_IsCameraRotate)
	{
		UpdateCameraRotate();
	}
}

void PlayerAnimationStateBase::LateUpdate()
{
	D3DXVECTOR3 vel = m_Manager->GetParameter()->m_Velocity;
	vel.y = 0.0f;
	float moveSpeed = D3DXVec3Length(&vel);

	UpdateSphereRotate(moveSpeed);
	UpdateCoverRotate(moveSpeed);
}

void PlayerAnimationStateBase::PreEnd()
{
	if (m_AnimationStepId != AnimationStepId::End)
	{
		m_AnimationStepId = AnimationStepId::PreEnd;
	}
}

void PlayerAnimationStateBase::End()
{
	m_AnimationStepId = AnimationStepId::End;
	m_IsCameraRotate = true;
}

void PlayerAnimationStateBase::UpdateParentRotateLock()
{
	D3DXQUATERNION q = Math::GetQuaternionIdentity();
	D3DXQuaternionInverse(&q, &m_Manager->GetParameter()->m_NowFrameRotateAngle);

	GameObject* rod = m_Manager->GetModelParts(PlayerManager::ModelPartsId::RodConnection);
	rod->m_LocalRotation *= q;
}

void PlayerAnimationStateBase::UpdateCameraRotate()
{
	// ���݂̖_�̈ʒu���猳�̖_�̈ʒu�܂Ŋ�����Ԃňړ�����
	D3DXVECTOR3 cameraForward = Manager::GetScene()->GetActiveCamera()->GetAttachObject()->GetForward();
	cameraForward = { cameraForward.x, 0.0f, cameraForward.z };
	cameraForward = Math::Normalize(cameraForward);

	GameObject* rodConnection = m_Manager->GetModelParts(PlayerManager::ModelPartsId::RodConnection);
	D3DXVECTOR3 rodForward = rodConnection->GetForward();
	rodForward = { rodForward.x, 0.0f, rodForward.z };
	rodForward = Math::Normalize(rodForward);

	D3DXVECTOR3 y = { 0.0f, 1.0f, 0.0f };
	D3DXVECTOR3 axis;
	D3DXQUATERNION q = Math::GetQuaternionIdentity();

	// �U������Ɏg����]��������
	if (rodForward == -cameraForward)
	{// z���Ɛ����ȏꍇ
		// �O�ς̌��ʂ����������Ȃ�̂Ŏ蓮�Ŏw��
		axis = y;
	}
	else
	{// z���Ɛ����ł͂Ȃ��ꍇ
		// �O�ς��g�����Ƃŋ߂�����������]�������߂���
		D3DXVec3Cross(&axis, &rodForward, &cameraForward);
	}

	// ���݂̌����ƌ������������Ƃ̂Ȃ��p�����߂�
	float angle = Math::VectorAngle(rodForward, cameraForward);
	angle *= m_CAMERA_FOLLOW_ROTATE_INTERPOLATION_RATE;
	// ��]�N�I�[�^�j�I�������
	q *= Math::AxisRotation_Radian(axis, angle);
	// ��]�̔��f
	rodConnection->m_LocalRotation *= q;
}

void PlayerAnimationStateBase::UpdateSphereRotate(float MoveSpeed)
{
	if (MoveSpeed != 0.0f)
	{
		float rotateSpeed = MoveSpeed * m_SPHERE_ROTATE_SPEED;
		m_Manager->GetModelParts(PlayerManager::ModelPartsId::Sphere)->m_LocalRotation *=
			Math::AxisRotation_Degree({ 1.0f, 0.0f, 0.0f }, rotateSpeed);
	}
}

void PlayerAnimationStateBase::UpdateCoverRotate(float MoveSpeed)
{
	m_AnimationBaseParam.CoverRotateTargetAngle = MoveSpeed * m_COVER_ROTATE_ANGLE_RATE;
	if (m_AnimationBaseParam.CoverRotateTargetAngle > m_COVER_ROTATE_ANGLE_MAX)
	{
		m_AnimationBaseParam.CoverRotateTargetAngle = m_COVER_ROTATE_ANGLE_MAX;
	}

	m_AnimationBaseParam.CoverRotateAngle += 
		(m_AnimationBaseParam.CoverRotateTargetAngle - m_AnimationBaseParam.CoverRotateAngle) * m_COVER_ROTATE_INTERPOLATION_RATE;

	m_Manager->GetModelParts(PlayerManager::ModelPartsId::Cover)->m_LocalRotation =
		Math::AxisRotation_Degree({ 1.0f, 0.0f, 0.0f }, -m_AnimationBaseParam.CoverRotateAngle);
}
