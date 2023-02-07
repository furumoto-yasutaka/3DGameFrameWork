/*******************************************************************************
*
*	�^�C�g���F	�f�o�b�O�p�J��������X�N���v�g	[ debugCameraControl.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "debugCameraControl.h"
#include "gameObject.h"
#include "input.h"

void DebugCameraControl::Update()
{
	//-----------------
	// ���_����
	//-----------------
	// ���͂��擾
	if (Input::GetMousePress(Input::MouseButton::Right))
	{
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

	if (Input::GetKeyboardPress(DIK_W))
	{
		m_AttachObject->m_LocalPosition += m_AttachObject->GetForward() * m_MoveSpeed;
	}
	if (Input::GetKeyboardPress(DIK_S))
	{
		m_AttachObject->m_LocalPosition -= m_AttachObject->GetForward() * m_MoveSpeed;
	}
	if (Input::GetKeyboardPress(DIK_A))
	{
		m_AttachObject->m_LocalPosition -= m_AttachObject->GetRight() * m_MoveSpeed;
	}
	if (Input::GetKeyboardPress(DIK_D))
	{
		m_AttachObject->m_LocalPosition += m_AttachObject->GetRight() * m_MoveSpeed;
	}
}