/*******************************************************************************
*
*	タイトル：	カメラコンポーネント	[ camera.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "camera.h"
#include "renderer.h"
#include "gameObject.h"
#include "manager.h"

void Camera::Init(bool IsActive)
{
	if (IsActive)
	{
		// アクティブカメラに設定する
		Manager::GetScene()->SetActiveCamera(this);
	}
}

void Camera::LateUpdate()
{
	// 自身がアクティブカメラの場合定数バッファにポジションを埋め込む
	if (Manager::GetScene()->GetActiveCamera() == this)
	{
		SetStructuredBuffer();
	}
}

void Camera::Draw()
{
	// アクティブ状態のカメラでない場合は終了する
	if (Manager::GetScene()->GetActiveCamera() != this) { return; }

	// ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 pos = m_AttachObject->GetWorldPosition();
	D3DXVECTOR3 target = m_AttachObject->m_LocalPosition + m_AttachObject->GetForward();
	D3DXMatrixLookAtLH(&m_ViewMatrix, &pos, &target, &up);
	Renderer::SetViewMatrix(&m_ViewMatrix);

	// プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f,
		(float)WINDOW_RESOLUTION_WIDTH / WINDOW_RESOLUTION_HEIGHT,
		0.1f, 1000.0f);
	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

bool Camera::CheckFrustumCulling(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	// カメラからオブジェクトのベクトル
	v = Position - m_AttachObject->m_LocalPosition;

	// 左→下→右→上の順で判定する
	for (int i = 0; i < 4; i++)
	{
		v1 = wpos[i] - m_AttachObject->m_LocalPosition;
		D3DXVec3Normalize(&v1, &v1);
		v2 = wpos[(i + 1) % 4] - m_AttachObject->m_LocalPosition;
		D3DXVec3Normalize(&v2, &v2);

		// 外積計算
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < -3.0f)
		{
			return false;
		}
	}

	return true;
}

void Camera::SetStructuredBuffer()
{
	Renderer::SetCameraPosition(m_AttachObject->GetWorldPosition());
}
