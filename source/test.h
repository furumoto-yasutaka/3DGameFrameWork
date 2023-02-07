/*******************************************************************************
*
*	タイトル：	タイトルシーンクラス	[ test.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "scene.h"
#include "gameObject.h"

// コンポーネント
#include "camera.h"
#include "Plate2dRenderer.h"
#include "modelRenderer.h"
#include "thirdPersonCamera.h"
#include "particleSystem.h"
#include "particleEmitChecker.h"

// スクリプト
#include "debugCameraControl.h"
#include "testScript.h"
#include "testScript2.h"
#include "playerManager.h"
#include "eggEnemyManager.h"
#include "collisionContactRecorder.h"
#include "collisionContactRecorder_PlayerGround.h"
#include "collisionContactRecorder_PlayerAttack.h"
#include "collisionContactRecorder_EnemyAttack.h"
#include "playerHpManager.h"


class Test : public Scene
{
	void Init() override
	{
		m_Tag = SceneTag::Test;
		GameObject* obj;
		GameObject* parent;
		GameObject* player;

		player = CreatePlayer();
		CreateEnemy();


		//ParticleSystem::EmitParam emitParam = {
		//	true, 20.0f, 10,
		//	{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f },
		//	ParticleSystem::SimulationSpaceId::World,
		//	ParticleSystem::EmitterStopActionId::ObjectDestroy,
		//};
		//ParticleSystem::ParticleDefaultParam particleDefaultParam = {
		//	1.0f, Math::MinMax<D3DXVECTOR2>({ 1.0f, 1.0f }, { 2.0f, 2.0f }),
		//	Math::MinMax<D3DXVECTOR3>({ -0.1f, -0.1f, -0.1f }, { 0.1f, 0.1f, 0.1f }),
		//	{ 0.0f, -0.001f, 0.0f }, "DevelopLogo", { 1.0f, 1.0f, 1.0f, 1.0f },
		//};
		//obj = AddGameObject("ParticleTest");
		//obj->AddComponent<ParticleSystem>()->Init(0.0f, true,
		//	emitParam, particleDefaultParam,
		//	new ParticleEmitChacker_RateOverTime(3.0f));


		// カメラ
		obj = AddGameObject("Camera");
		obj->m_LocalPosition = { 0.0f, 0.0f, -5.0f };
		//obj->AddComponent<Camera>()->Init(true);
		//obj->AddComponent<DebugCameraControl>()->Init();
		obj->AddComponent<ThirdPersonCamera>()->Init( true, ThirdPersonCamera::InputModeId::Mouse, player, { 0.0f, 1.0f, -7.0f });

		// 地面
		obj = AddGameObject("Platform1", (int)Scene::ObjLayer::Default, (int)Scene::ObjTag::Platform);
		obj->m_LocalPosition = { 0.0f, -5.0f, 0.0f };
		obj->m_LocalScale = { 100.0f, 1.0f, 100.0f };
		obj->AddComponent<ModelRenderer>()->Init("Platform_Cube");
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, false, true);

		// 地面
		obj = AddGameObject("Platform2", (int)Scene::ObjLayer::Default, (int)Scene::ObjTag::Platform);
		obj->m_LocalPosition = { 20.0f, 0.0f, 0.0f };
		obj->m_LocalScale = { 10.0f, 10.0f, 10.0f };
		obj->AddComponent<ModelRenderer>()->Init("Platform_Cube");
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, false, true);


		Scene::Init();
		Scene::LateInit();
	}

	void Update() override
	{
		Scene::Update();
	}

	GameObject* CreatePlayer()
	{
		// ┳プレイヤールート							Player
		// ┣━地面接地判定用コリジョン					Player_GroundCollision
		// ┗┳モデルルート								Player_Model_Loot
		// 　┣━凹凸球モデル							Player_Model_Sphere
		// 　┗┳カバーモデル							Player_Model_Cover
		// 	 　┗┳棒接続部モデル						Player_Model_RodConnection
		// 	 　　┗┳棒中心オブジェクト					Player_Model_RodCenter
		//　　　 　┗┳棒グループ						Player_Model_Rod
		// 	   　　　┣━棒(前半)モデル					Player_Model_RodFirstHalf
		// 	   　　　┣┳棒(後半)グループ				Player_Model_RodLetterHalf
		// 	     　　┃┣━棒(後半左)モデル				Player_Model_RodLetterHalf_Left
		// 	     　　┃┗━棒(後半右)モデル				Player_Model_RodLetterHalf_Right
		// 　　　　　┗━棒にくっついた敵				Player_Model_RodLetterHalf

		GameObject* player;
		GameObject* parent;
		GameObject* obj;
		GameObject* obj2;

		// プレイヤー
		player = AddGameObject("Player", (int)ObjLayer::Default, (int)ObjTag::Player);
		player->m_LocalPosition = { 0.0f, 0.0f, -30.0f };
		player->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f });
		player->AddComponent<PlayerManager>()->Init(PlayerManager::InputModeId::MouseKeyboard);

		obj = AddGameObject("Player_GroundCollision");
		obj->SetParent(player);
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, -0.6f, 0.0f }, { 0.45f, 0.05f, 0.45f }, true);
		obj->AddComponent<CollisionContactRecorder_PlayerGround<AABBCollider3D>>()->Init((int)Scene::ObjTag::Platform);

		obj = AddGameObject("Player_Model_Loot");
		obj->SetParent(player);

		parent = obj;

		obj = AddGameObject("Player_Model_Sphere");
		obj->SetParent(parent);
		obj->AddComponent<ModelRenderer>()->Init("Player_Sphere", "toonVS", "toonPS");

		obj = AddGameObject("Player_Model_Cover");
		obj->SetParent(parent);
		obj->AddComponent<ModelRenderer>()->Init("Player_Cover", "toonVS", "toonPS");

		parent = obj;

		obj = AddGameObject("Player_Model_RodConnection");
		obj->SetParent(parent);
		obj->m_LocalPosition = { 0.0f, 0.5f, 0.0f };
		obj->AddComponent<ModelRenderer>()->Init("Player_RodConnection", "toonVS", "toonPS");

		parent = obj;

		obj = AddGameObject("Player_Model_RodCenter");
		obj->SetParent(parent);
		obj->m_LocalPosition = { 0.0f, 0.2f, 0.0f };
		obj->m_LocalScale = { 0.0f, 0.0f, 0.0f };

		parent = obj;

		obj = AddGameObject("Player_Model_Rod");
		obj->SetParent(parent);
		obj->m_LocalPosition = { 0.0f, 0.0f, 0.5f };
		obj->AddComponent<OBBCollider3D>()->Init({ 0.0f, 0.0f, -0.5f }, { 0.1f, 0.2f, 2.5f }, true);
		obj->AddComponent<CollisionContactRecorder_PlayerAttack<OBBCollider3D>>()->Init((int)Scene::ObjTag::Enemy);

		parent = obj;

		obj = AddGameObject("Player_Model_RodFirstHalf");
		obj->SetParent(parent);
		obj->AddComponent<ModelRenderer>()->Init("Player_RodFirstHalf", "toonVS", "toonPS");

		obj = AddGameObject("Player_Model_RodLetterHalf");
		obj->SetParent(parent);

		obj2 = AddGameObject("Player_StickEnemyList");
		obj2->SetParent(parent);

		parent = obj;

		obj = AddGameObject("Player_Model_RodLetterHalf_Left");
		obj->SetParent(parent);
		obj->m_LocalPosition = { -0.0375f, 0.0f, 0.0f };
		//obj->m_LocalRotation = Math::AxisRotation_Degree({0.0f, 1.0f, 0.0f}, -90.0f);
		obj->AddComponent<ModelRenderer>()->Init("Player_RodLetterHalf", "toonVS", "toonPS");

		obj = AddGameObject("Player_Model_RodLetterHalf_Right");
		obj->SetParent(parent);
		obj->m_LocalPosition = { 0.0375f, 0.0f, 0.0f };
		//obj->m_LocalRotation = Math::AxisRotation_Degree({ 0.0f, 1.0f, 0.0f }, 90.0f);
		obj->AddComponent<ModelRenderer>()->Init("Player_RodLetterHalf", "toonVS", "toonPS");


		// プレイヤーHP
		parent = AddGameObject(PlayerManager::m_PLAYER_HP_MANAGER_OBJ_NAME);
		parent->m_LocalPosition = { 10.0f, 10.0f, 0.0f };
		parent->AddComponent<PlayerHpManager>()->Init();


		return player;
	}

	GameObject* CreateEnemy()
	{
		GameObject* enemy;
		GameObject* parent;
		GameObject* obj;

		OBBCollider3D* obbColider;

		// ●たまご
		// ┳エネミールート					Enemy_Egg
		// ┣━接地判定用コリジョン			Enemy_GroundCollision
		// ┣━探知判定用コリジョン			Enemy_SearchCollision
		// ┣━攻撃判定用コリジョン			Enemy_AttackCollision
		// ┣━ジャンプ判定用コリジョン		Enemy_JumpCollision
		// ┗┳モデルルート					Enemy_Model_Loot
		// 　┗━たまごモデル				Enemy_Model_Egg

		enemy = AddGameObject("Enemy_Egg", (int)ObjLayer::Default, (int)ObjTag::Enemy);
		enemy->m_LocalPosition = { 0.0f, 0.0f, 0.0f };
		enemy->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.2f, 0.0f }, { 0.5f, 0.75f, 0.5f });
		enemy->AddComponent<EggEnemyManager>()->Init();

		obj = AddGameObject("Enemy_GroundCollision");
		obj->SetParent(enemy);
		obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, -0.6f, 0.0f }, { 0.45f, 0.05f, 0.45f }, true);
		obj->AddComponent<CollisionContactRecorder<AABBCollider3D>>()->Init((int)Scene::ObjTag::Platform);

		obj = AddGameObject("Enemy_SearchCollision");
		obj->SetParent(enemy);
		obbColider = obj->AddComponent<OBBCollider3D>();
		obbColider->Init({ 0.0f, 0.0f, 0.0f }, { 0.1f, 0.1f, 0.1f }, true);//
		obj->AddComponent<CollisionContactRecorder<OBBCollider3D>>()->Init((int)Scene::ObjTag::Player);

		obj = AddGameObject("Enemy_AttackCollision");
		obj->SetParent(enemy);
		obbColider = obj->AddComponent<OBBCollider3D>();
		obbColider->Init({ 0.0f, 0.0f, 0.0f }, { 0.1f, 0.1f, 0.1f }, true);//
		obj->AddComponent<CollisionContactRecorder_EnemyAttack<OBBCollider3D>>()->Init((int)Scene::ObjTag::Player);

		obj = AddGameObject("Enemy_JumpCollision");
		obj->SetParent(enemy);
		obbColider = obj->AddComponent<OBBCollider3D>();
		obbColider->Init({ 0.0f, 0.2f, 1.0f }, { 0.25f, 0.25f, 0.1f }, true);
		obj->AddComponent<CollisionContactRecorder<OBBCollider3D>>()->Init((int)Scene::ObjTag::Platform);
		
		obj = AddGameObject("Enemy_Model_Loot");
		obj->SetParent(enemy);

		parent = obj;

		obj = AddGameObject("Enemy_Model_Egg");
		obj->SetParent(parent);
		obj->AddComponent<ModelRenderer>()->Init("Enemy_Egg", "toonVS", "toonPS");

		return enemy;

		//// ●ひよこ
		//// ┳エネミールート								Enemy_Chick
		//// ┣━地面接地判定用コリジョン					Enemy_GroundCollision
		//// ┗┳モデルルート								Enemy_Model_Loot
		//// 　┗━ひよこモデル							Enemy_Model_Chick

		//enemy = AddGameObject("Enemy_Chick");
		//enemy->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f });

		//obj = AddGameObject("Enemy_GroundCollision");
		//obj->SetParent(enemy);
		//obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, -0.6f, 0.0f }, { 0.45f, 0.05f, 0.45f }, true);
		//obj->AddComponent<PlayerGroundCollision>()->Init();

		//obj = AddGameObject("Enemy_Model_Loot");
		//obj->SetParent(enemy);

		//parent = obj;

		//obj = AddGameObject("Enemy_Model_Chick");
		//obj->SetParent(parent);
		//obj->AddComponent<ModelRenderer>()->Init("Enemy_Chick");



		//// ●にわとり
		//// ┳エネミールート								Enemy_Chicken
		//// ┣━地面接地判定用コリジョン					Enemy_GroundCollision
		//// ┗┳モデルルート								Enemy_Model_Loot
		//// 　┗━にわとりモデル							Enemy_Model_Chicken

		//enemy = AddGameObject("Enemy_Chicken");
		//enemy->AddComponent<AABBCollider3D>()->Init({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f });

		//obj = AddGameObject("Enemy_GroundCollision");
		//obj->SetParent(enemy);
		//obj->AddComponent<AABBCollider3D>()->Init({ 0.0f, -0.6f, 0.0f }, { 0.45f, 0.05f, 0.45f }, true);
		//obj->AddComponent<PlayerGroundCollision>()->Init();

		//obj = AddGameObject("Enemy_Model_Loot");
		//obj->SetParent(enemy);

		//parent = obj;

		//obj = AddGameObject("Enemy_Model_Chicken");
		//obj->SetParent(parent);
		//obj->AddComponent<ModelRenderer>()->Init("Enemy_Chicken");
	}
};
