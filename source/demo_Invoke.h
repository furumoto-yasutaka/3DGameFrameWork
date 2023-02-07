/*******************************************************************************
*
*	タイトル：	Invoke紹介シーンクラス	[ demo_Invoke.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "scene.h"
#include "gameObject.h"

// コンポーネント
#include "camera.h"
#include "plate3dRenderer.h"

// スクリプト
#include "testInvoke.h"
#include "debugCameraControl.h"

class Demo_Invoke : public Scene
{
	void Init() override
	{
		m_Tag = SceneTag::Demo_Invoke;
		GameObject* obj;



		obj = AddGameObject("Tex");
		obj->AddComponent<Plate3DRenderer>()->Init("DevelopLogo", { 1.0f, 1.0f });
		obj->AddComponent<TestInvoke>()->Init();


		// カメラ
		obj = AddGameObject("Camera");
		obj->m_LocalPosition = { 0.0f, 0.0f, -5.0f };
		obj->AddComponent<Camera>()->Init(true);
		obj->AddComponent<DebugCameraControl>()->Init();



		Scene::Init();
		Scene::LateInit();
	}

	void Update() override
	{
		Scene::Update();
	}
};
