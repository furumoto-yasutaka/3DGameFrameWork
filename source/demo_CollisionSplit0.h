/*******************************************************************************
*
*	�^�C�g���F	8���؋�ԕ����V�[���N���X	[ demo_CollisionSplit0.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "scene.h"
#include "gameObject.h"
#include "collision3dManager.h"

// �R���|�[�l���g
#include "camera.h"
#include "plate3dRenderer.h"
#include "aabbCollider3d.h"

// �X�N���v�g
#include "testMove.h"
#include "debugCameraControl.h"

class Demo_CollisionSplit0 : public Scene
{
	void Init() override
	{
		m_Tag = SceneTag::Demo_CollisionSplit0;
		GameObject* obj;


		// �R���W����
		D3DXVECTOR3 colSize = { 1.0f, 1.0f, 1.0f };

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, 5.0f, 5.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -35.0f, 10.0f, -30.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ -10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -20.0f, -10.0f, 35.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, 30.0f, -15.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ -10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 20.0f, 5.0f, 15.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 24.0f, 5.0f, 15.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ -10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -35.0f, -10.0f, -20.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 10.0f, -10.0f, 5.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ -10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, 5.0f, 15.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 10.0f, 0.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 30.0f, 30.0f, 30.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ -10.0f, 0.0f, 0.0f });


		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -30.0f, -35.0f, 5.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 20.0f, 35.0f, 35.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, -10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 10.0f, 20.0f, -35.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -10.0f, -30.0f, 20.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, -10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 35.0f, -35.0f, 35.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -30.0f, -30.0f, 30.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, -10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 20.0f, 20.0f, 20.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -10.0f, 30.0f, -40.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, -10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -20.0f, 30.0f, -20.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 10.0f, 0.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 30.0f, -15.0f, 20.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, -10.0f, 0.0f });


		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 30.0f, -20.0f, -10.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, 10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 35.0f, 20.0f, 40.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, -10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -10.0f, 5.0f, -35.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, 10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -35.0f, 5.0f, -10.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, -10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, -35.0f, 5.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, 10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, 5.0f, -10.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, -10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, 5.0f, 30.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, 10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -35.0f, 35.0f, 35.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, -10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { -35.0f, 5.0f, 5.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, 10.0f });

		obj = AddGameObject("Collision");
		obj->m_LocalPosition = { 5.0f, 30.0f, 5.0f };
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, colSize, true);
		obj->AddComponent<TestMove>()->Init({ 0.0f, 0.0f, -10.0f });


		// �J����
		obj = AddGameObject("Camera");
		obj->m_LocalPosition = { -40.0f, 10.0f, -50.0f };
		obj->m_LocalRotation = Math::AxisRotation_Degree({ 1.0f, 0.0f, 0.0f }, 20.0f);
		obj->m_LocalRotation = Math::AxisRotation_Degree({ 0.0f, 1.0f, 0.0f }, 25.0f);
		obj->AddComponent<Camera>()->Init(true);
		obj->AddComponent<DebugCameraControl>()->Init();


		Collision3DManager::ResetSpace(0, Collision3DManager::GetMin(), Collision3DManager::GetSize());

		Scene::Init();
		Scene::LateInit();
	}

	void Update() override
	{
		Scene::Update();
	}
};
