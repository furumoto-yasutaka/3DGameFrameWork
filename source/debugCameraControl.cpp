/*******************************************************************************
*
*	タイトル：	デバッグ用カメラ制御スクリプト	[ debugCameraControl.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "debugCameraControl.h"
#include "gameObject.h"
#include "input.h"

void DebugCameraControl::Update()
{
	//-----------------
	// 視点操作
	//-----------------
	// 入力を取得
	if (Input::GetMousePress(Input::MouseButton::Right))
	{
		m_RotateXValue += Input::GetMouseMoveY() * m_RotateSenseY;
		m_RotateYValue += Input::GetMouseMoveX() * m_RotateSenseX;
		// 一定の角度で制限
		if (m_RotateXValue > m_RotateMaxX) { m_RotateXValue = m_RotateMaxX; }
		else if (m_RotateXValue < -m_RotateMaxX) { m_RotateXValue = -m_RotateMaxX; }
		// 回転を反映
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