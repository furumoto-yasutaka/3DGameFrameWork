/*******************************************************************************
*
*	タイトル：	モデル管理用静的クラス	[ modelContainer.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "modelContainer.h"
#include "manager.h"
#include "scene.h"

void ModelContainer::Init()
{
	// スカイドーム用
	AddModel("SkyDome", "SkyDome.obj", (int)Scene::SceneTag::Everything);

	// プレイヤー
	AddModel("Coconut",					"Game\\Coconut\\coconut.obj",				(int)Scene::SceneTag::Everything);
	AddModel("Player_Sphere",			"Game\\Player\\PlayerSphere.obj",			(int)Scene::SceneTag::Everything);
	AddModel("Player_Cover",			"Game\\Player\\PlayerCover.obj",			(int)Scene::SceneTag::Everything);
	AddModel("Player_RodConnection",	"Game\\Player\\PlayerRodConnection.obj",	(int)Scene::SceneTag::Everything);
	AddModel("Player_RodFirstHalf",		"Game\\Player\\PlayerRodFirstHalf.obj",		(int)Scene::SceneTag::Everything);
	AddModel("Player_RodLetterHalf",	"Game\\Player\\PlayerRodLetterHalf.obj",	(int)Scene::SceneTag::Everything);

	// エネミー
	AddModel("Enemy_Egg", "Game\\Egg\\egg.obj", (int)Scene::SceneTag::Everything);

	// プラットフォーム
	AddModel("Platform_Cube", "Game\\Platform\\Cube.obj", (int)Scene::SceneTag::Test);
}

void ModelContainer::Uninit()
{
	// すべてのモデルを解放
	for (auto itr : m_ModelInfo)
	{
		itr.second->Unload(true);
	}
	for (auto itr : m_ModelInfo)
	{
		if (itr.second) { delete itr.second; }
	}
}

/*******************************************************************************
*	すべてのモデルに対してタグに応じて
*	ロード・アンロードを実行(シーン変更時用)
*******************************************************************************/
void ModelContainer::LoadAndUnload_AllModel()
{
	for (auto itr = m_ModelInfo.begin(); itr != m_ModelInfo.end(); itr++)
	{
		if (itr->second->GetTag() & Manager::GetScene()->GetTag())
		{// 次のシーンで使う場合
			itr->second->Load();
		}
		else
		{// 次のシーンで使わない場合
			itr->second->Unload();
		}
	}
}

/*******************************************************************************
*	モデル取得(名称で検索)
*******************************************************************************/
Model* ModelContainer::GetModel_InName(string Name)
{
	decltype(m_ModelInfo)::iterator itr = m_ModelInfo.find(Name);
	if (itr != m_ModelInfo.end())
	{
		return itr->second;
	}
	else
	{
		string str = string("存在しない名称のモデルの取得が要求されました。\n") + Name;
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("modelContainer:Error"),
			MB_OK | MB_ICONERROR);
		return NULL;
	}
}

/*******************************************************************************
*	モデル追加
*******************************************************************************/
void ModelContainer::AddModel(string Name, string Path, int Tag)
{
	string fullPath = "asset\\model\\" + Path;

	// 要素がマップに存在するか確認
	if (m_ModelInfo.find(Name) != m_ModelInfo.end())
	{
		string str = string("すでに存在する名称でモデルの追加が要求されました。\n") + fullPath + "\nこのモデルは読み込まれません。";
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("modelContainer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_ModelInfo[Name] = DBG_NEW Model(fullPath.c_str());
		m_ModelInfo[Name]->AddTag(Tag);
	}
}
