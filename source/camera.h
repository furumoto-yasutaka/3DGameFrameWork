/*******************************************************************************
*
*	タイトル：	カメラコンポーネント	[ camera.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"

class Camera : public SystemComponent
{
protected:
	D3DXMATRIX m_ViewMatrix;	// カメラの姿勢
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
	//　↓↓　アクセサ　↓↓　//
	virtual D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	/////////////////////////////
};
