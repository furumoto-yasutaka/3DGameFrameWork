/*******************************************************************************
*
*	タイトル：	三人称視点カメラコンポーネント	[ thirdPersonCamera.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "thirdPersonCamera.h"
#include "renderer.h"
#include "gameObject.h"
#include "input.h"
#include "manager.h"

void ThirdPersonCamera::Init(bool IsActive, InputModeId InputMode,
	GameObject* FollowObject, D3DXVECTOR3 FollowOffset)
{
	Camera::Init(IsActive);
	m_InputMode = InputMode;
	m_FollowObject = FollowObject;
	m_FollowOffset = FollowOffset;
	m_RotateValue = { 0.0f, 0.0f };

	m_Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void ThirdPersonCamera::Uninit()
{

}

void ThirdPersonCamera::Update()
{
	//-----------------
	// 視点操作
	//-----------------
	// 入力を取得
	m_RotateValue += GetRotateInput();
	// 一定の角度で制限
	if (m_RotateValue.x > m_RotateMaxX) { m_RotateValue.x = m_RotateMaxX; }
	else if (m_RotateValue.x < -m_RotateMaxX) { m_RotateValue.x = -m_RotateMaxX; }
	// 回転を反映
	D3DXQuaternionIdentity(&m_AttachObject->m_LocalRotation);
	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_RotateValue.y);
	m_AttachObject->m_LocalRotation *= Math::AxisRotation_Degree(m_AttachObject->GetRight(), m_RotateValue.x);
}

void ThirdPersonCamera::LateUpdate()
{
	SystemComponent::LateUpdate();

	//-----------------
	// カメラ追従
	//-----------------
	if (m_FollowObject)
	{
		D3DXVECTOR3 distance = (m_FollowObject->GetWorldPosition() + m_FollowOffset) - m_AttachObject->m_LocalPosition;
		m_AttachObject->m_LocalPosition += distance * m_FollowSpeed;
	}
	else
	{
		m_AttachObject->m_LocalPosition = m_FollowOffset;
	}

	D3DXVECTOR3 follow = m_AttachObject->m_LocalPosition - m_FollowOffset;
	D3DXVECTOR3 offset = m_FollowOffset + m_Offset;
	D3DXMATRIX rot, trans1, trans2;

	D3DXMatrixTranslation(&trans1, follow.x, follow.y, follow.z);
	D3DXMatrixRotationQuaternion(&rot, &m_AttachObject->m_LocalRotation);
	D3DXMatrixTranslation(&trans2, offset.x, offset.y, offset.z);

	// 追尾分のみ座標を移動 → 原点を中心に回転 → 設定したオフセット分座標を移動
	m_CameraMatrix = trans2 * rot * trans1;

	// ビューマトリクスはカメラの移動ではなく
	// カメラ以外の全ての影響になるので逆行列を設定
	D3DXMatrixInverse(&m_ViewMatrix, NULL, &m_CameraMatrix);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	Camera::LateUpdate();
}

void ThirdPersonCamera::Draw()
{
	// アクティブ状態のカメラでない場合は終了する
	if (Manager::GetScene()->GetActiveCamera() != this) { return; }

	// プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,
		(float)WINDOW_RESOLUTION_WIDTH / WINDOW_RESOLUTION_HEIGHT,
		0.1f, 1000.0f);
	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

D3DXVECTOR2 ThirdPersonCamera::GetRotateInput()
{
	D3DXVECTOR2 v;

	switch (m_InputMode)
	{
		using enum InputModeId;
	case Mouse:
		v = { Input::GetMouseMoveY() * m_RotateSenseMouse.y,
			Input::GetMouseMoveX() * m_RotateSenseMouse.x };
		break;
	case Controller:
		v = { Input::GetGamePadStickRightY() * m_RotateSenseController.y,
			Input::GetGamePadStickRightX() * m_RotateSenseController.x };
		break;
	default:
		v = { 0.0f, 0.0f };
		break;
	}

	if (m_IsRotateXReverse) { v.x = -v.x; }
	if (m_IsRotateYReverse) { v.y = -v.y; }

	return v;
}

void ThirdPersonCamera::SetStructuredBuffer()
{
	D3DXVECTOR3 p = { m_CameraMatrix._41, m_CameraMatrix._42, m_CameraMatrix._43 };
	Renderer::SetCameraPosition(p);
}
