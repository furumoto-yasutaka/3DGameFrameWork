/*******************************************************************************
*
*	タイトル：	ゲーム全体管理用静的クラス	[ manager.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "manager.h"

// 静的クラス
#include "renderer.h"
#include "time.h"
#include "input.h"
#include "modelContainer.h"
#include "textureContainer.h"
#include "audioContainer.h"
#include "skyDome.h"
#include "savedataManager.h"
#include "collision3dManager.h"
#include "collider3d.h"
#include "debugManager.h"
#ifdef _DEBUG
#include "debugConsole.h"
#endif

// 一番最初に開始するシーン
#include "test.h"
#include "demo_Invoke.h"
#include "demo_Parent.h"
#include "demo_CollisionSplit0.h"

#include <typeinfo>

void Manager::Init(HINSTANCE hInstance)
{
	// 静的クラスの初期化
#ifdef _DEBUG
	DebugConsole::Init();
#endif
	Renderer::Init();
	Input::Init(hInstance);
	TextureContainer::Init();
	ModelContainer::Init();
	AudioContainer::Init();
	SkyDome::Init();
	Transition::Init();
	SavedataManager::Init();
	Collision3DManager::Init(3, D3DXVECTOR3(-50.0f, -50.0f, -50.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));

#ifdef _DEBUG
	DebugManager::Init();
#endif

	// 最初のシーンを起動
	SetScene<Demo_Parent>(Transition::GetFirstTransitionOption());
	CheckScene();

	// ロード時間も計測時間に入れてしまうので最後に行う
	Time::Init();
}

void Manager::Uninit()
{
	// 初期化と逆順に終了処理を行う
	m_Scene->Uninit();
	delete m_Scene;

	Collision3DManager::Uninit();
	SavedataManager::Uninit();
	Transition::Uninit();
	SkyDome::Uninit();
	AudioContainer::Uninit();
	ModelContainer::Uninit();
	TextureContainer::Uninit();
	Input::Uninit();
	Time::Uninit();
	Renderer::Uninit();
#ifdef _DEBUG
	DebugConsole::Uninit();
	DebugManager::Uninit();
#endif
}

void Manager::Update()
{
	// 静的クラス更新
#ifdef _DEBUG
	DebugConsole::Update();
#endif
	Time::Update();
	Input::Update();

	// シーン更新
	m_Scene->Update();

	// オブジェクトの更新後に衝突判定を行う
	Collision3DManager::Update();

	// 描画のタイミングに合わせてシーンの後に行う
	Transition::Update();

	// オブジェクトの削除を確認する
	m_Scene->CheckObjectDestroy();

#ifdef _DEBUG
	// デバッグ情報を表示
	DebugManager::Update();
#endif

	// シーン遷移を行うか確認
	CheckScene();
}

void Manager::Draw()
{
	// 背景をクリアする
	Renderer::Begin();

	Collision3DManager::Draw();

	// シーン内オブジェクト描画
	m_Scene->Draw();

	// トランジションが一番手前でなければならないためこのタイミング
	Transition::Draw();

#ifdef _DEBUG
	DebugManager::Draw();
#endif

	// 画面をスワップ
	Renderer::End();
}

/*******************************************************************************
*	シーン遷移を行うか確認
*******************************************************************************/
void Manager::CheckScene()
{
	// 予約が無い場合またはトランジション中の場合は遷移せず終了する
	if (!m_NextScene ||
		Transition::GetTransitionState() == Transition::TransitionState::Out)
	{ return; }

	//------------------------
	// 遷移処理
	//------------------------
	if (m_Scene)
	{
		// 現在までのシーンを削除
		m_Scene->Uninit();
		delete m_Scene;
	}

	// 予約したシーンに切り替え
	m_Scene = m_NextScene;
	m_NextScene = nullptr;

	// 初期化
	m_Scene->Init();
	Transition::StartTransitionIn();
}
