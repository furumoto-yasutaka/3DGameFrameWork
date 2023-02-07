/*******************************************************************************
*
*	タイトル：	デバッグ用カメラ制御スクリプト	[ debugCameraControl.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class DebugCameraControl : public ScriptComponent
{
private:
	float		m_RotateSenseX = 0.15f;	// 回転感度(X)
	float		m_RotateSenseY = 0.1f;	// 回転感度(Y)
	float		m_RotateMaxX = 60.0f;	// 回転上限(X)
	float		m_MoveSpeed = 0.1f;		// 移動速度

	float		m_RotateXValue = 0.0f;	// ローカルX方向への回転量
	float		m_RotateYValue = 0.0f;	// ローカルY方向への回転量

public:
	DebugCameraControl(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init() {}
	void Uninit() override {}
	void Update() override;
	void Draw() override {}
};