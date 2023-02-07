/*******************************************************************************
*
*	タイトル：	一人称視点カメラコンポーネント	[ firstPersonCamera.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"
#include "camera.h"

class FirstPersonCamera : public Camera
{
private:
	GameObject* m_FollowObject = NULL;	// 追尾対象オブジェクト
	D3DXVECTOR3	m_FollowOffset;			// 追尾座標オフセット値
	float		m_RotateSenseX = 0.15f;	// 回転感度(X)
	float		m_RotateSenseY = 0.1f;	// 回転感度(Y)
	float		m_RotateMaxX = 60.0f;	// 回転上限(X)

	float		m_RotateXValue = 0.0f;	// ローカルX方向への回転量
	float		m_RotateYValue = 0.0f;	// ローカルY方向への回転量

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
