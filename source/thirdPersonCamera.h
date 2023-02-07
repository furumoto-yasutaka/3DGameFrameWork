/*******************************************************************************
*
*	タイトル：	三人称視点カメラコンポーネント	[ thirdPersonCamera.h ]
*
*	作成者：	古本 泰隆
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
	GameObject* m_FollowObject = NULL;						// 追尾対象オブジェクト
	D3DXVECTOR3	m_FollowOffset;								// 追尾座標オフセット値
	bool		m_IsRotateXReverse = false;					// X軸回転の入力反転
	bool		m_IsRotateYReverse = false;					// Y軸回転の入力反転
	D3DXVECTOR2	m_RotateSenseMouse = { 0.15f, 0.1f };		// 回転感度(マウス)
	D3DXVECTOR2	m_RotateSenseController = { 2.0f, 1.0f };	// 回転感度(コントローラー)
	float		m_RotateMaxX = 60.0f;						// 回転上限(X)

	D3DXVECTOR2 m_RotateValue;				// ローカル方向への回転量
	float		m_FollowSpeed = 0.4f;		// 補間速度(0.0f < v <= 1.0f)

	D3DXMATRIX m_CameraMatrix;				// カメラの姿勢

public:
	D3DXVECTOR3 m_Offset;					// 外部から座標を操作するためのオフセット

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
	//　↓↓　アクセサ　↓↓　//
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
