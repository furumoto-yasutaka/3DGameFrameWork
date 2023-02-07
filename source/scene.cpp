/*******************************************************************************
*
*	タイトル：	シーン基底クラス	[ scene.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "scene.h"
#include "gameObject.h"
#include "draw2dComponent.h"
#include "modelContainer.h"
#include "textureContainer.h"
#include "audioContainer.h"
#include "skyDome.h"
#include "debugManager.h"

#include <typeinfo>
#include <algorithm>

void Scene::Init()
{
	InitAsset();
}

void Scene::LateInit()
{
	for (auto itr : m_GameObject_Ordered)
	{
		itr->LateInit();
	}
	for (auto itr : m_StaticGameObject_Ordered)
	{
		itr->LateInit();
	}
}

void Scene::Uninit()
{
	for (auto itr : m_GameObject_Ordered)
	{
		itr->Uninit();
		delete itr;
	}
	m_GameObject.clear();
	m_GameObject_Ordered.clear();
}

void Scene::Update()
{
	// 更新処理
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Update(i); }
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Update(i); }
		}
	}

	// 遅延更新処理
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive())
			{
				itr->LateUpdate(i);
				itr->CheckComponentDestroy();
			}
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive())
			{
				itr->LateUpdate(i);
				itr->CheckComponentDestroy();
			}
		}
	}
}

void Scene::Draw()
{
	// 描画処理
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		// 2D描画は最後に行うのでスキップする
		if (i == (int)Component::ProcGroup::Draw2D) { continue; }

		// スカイドームの描画は3D描画と一緒に行う
		if (i == (int)Component::ProcGroup::Draw3D) { SkyDome::Draw(); }

		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Draw(i); }
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Draw(i); }
		}
	}

#ifdef _DEBUG
	if (DebugManager::m_IsParentLine)
	{
		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive()) { itr->DrawDebug(); }
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive()) { itr->DrawDebug(); }
		}
	}
#endif

	// 2D描画のみ別途優先度順で行う
	for (auto itr : m_Draw2DComponentList_PriorityOrdered)
	{
		// コンポーネントの描画処理を直接呼ぶのでScene側で有効状態の確認をする
		if (!itr->GetActive() || !itr->GetAttachObject()->GetActive()) { continue; }
		itr->Draw();
	}
}

/*******************************************************************************
*	オブジェクト削除確認
*******************************************************************************/
void Scene::CheckObjectDestroy()
{
	// 動的オブジェクト
	auto itr = m_GameObject_Ordered.begin();
	while (itr != m_GameObject_Ordered.end())
	{
		if ((*itr)->GetIsDestroy())
		{
			m_GameObject.erase((*itr)->GetMapIterator());
			(*itr)->Destroy();
			itr = m_GameObject_Ordered.erase(itr);
		}
		else { itr++; }
	}

	// 静的オブジェクト
	itr = m_StaticGameObject_Ordered.begin();
	while (itr != m_StaticGameObject_Ordered.end())
	{
		if ((*itr)->GetIsDestroy())
		{
			m_StaticGameObject.erase((*itr)->GetMapIterator());
			(*itr)->Destroy();
			itr = m_StaticGameObject_Ordered.erase(itr);
		}
		else { itr++; }
	}
}

/*******************************************************************************
*	オブジェクトをシーンに追加
*******************************************************************************/
GameObject* Scene::AddGameObject(string Name, int Layer, int Tag, bool IsStatic)
{
	GameObject* gameObject = DBG_NEW GameObject();
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;
	
	// リストに追加し、イテレータを保存
	if (IsStatic)
	{// 静的オブジェクトとして追加
		mapItr = m_StaticGameObject.insert({ Name, gameObject });
		m_StaticGameObject_Ordered.push_back(gameObject);
		orderedListItr = m_StaticGameObject_Ordered.rbegin().base();
	}
	else
	{// 動的オブジェクトとして追加
		mapItr = m_GameObject.insert({ Name, gameObject });
		m_GameObject_Ordered.push_back(gameObject);
		orderedListItr = m_StaticGameObject_Ordered.rbegin().base();
	}

	gameObject->Init(Name, Layer, Tag, mapItr, orderedListItr);

	return gameObject;
}

/*******************************************************************************
*	静的オブジェクトに変更する
*******************************************************************************/
void Scene::SetStatic(GameObject* Object)
{
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;

	// 該当するオブジェクトを静的オブジェクトに移動する
	m_GameObject.erase(Object->GetMapIterator());
	m_GameObject_Ordered.erase(Object->GetOrderedListIterator());

	mapItr = m_StaticGameObject.insert({ Object->GetName(), Object });
	m_StaticGameObject_Ordered.push_back(Object);
	orderedListItr = m_StaticGameObject_Ordered.rbegin().base();

	Object->SetIterator(mapItr, orderedListItr);
}

/*******************************************************************************
*	動的オブジェクトに変更する
*******************************************************************************/
void Scene::SetDynamic(GameObject* Object)
{
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;

	// 該当するオブジェクトを静的オブジェクトに移動する
	m_StaticGameObject.erase(Object->GetMapIterator());
	m_StaticGameObject_Ordered.erase(Object->GetOrderedListIterator());

	mapItr = m_GameObject.insert({ Object->GetName(), Object });
	m_GameObject_Ordered.push_back(Object);
	orderedListItr = m_GameObject_Ordered.rbegin().base();

	Object->SetIterator(mapItr, orderedListItr);
}

/*******************************************************************************
*	オブジェクトの名前(キー)を変更する
*******************************************************************************/
void Scene::SetObjectName(GameObject* Object, string NewName)
{
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;
	list<GameObject*>::iterator prevOrderedListItr;

	if (Object->GetStatic())
	{// 静的オブジェクト
		m_StaticGameObject.erase(Object->GetMapIterator());
		mapItr = m_StaticGameObject.insert({ NewName, Object });

		prevOrderedListItr = Object->GetOrderedListIterator();
		orderedListItr = m_StaticGameObject_Ordered.insert(prevOrderedListItr, Object);
		m_StaticGameObject_Ordered.erase(prevOrderedListItr);
	}
	else
	{// 動的オブジェクト
		m_StaticGameObject.erase(Object->GetMapIterator());
		mapItr = m_StaticGameObject.insert({ NewName, Object });

		prevOrderedListItr = Object->GetOrderedListIterator();
		orderedListItr = m_StaticGameObject_Ordered.insert(prevOrderedListItr, Object);
		m_StaticGameObject_Ordered.erase(prevOrderedListItr);
	}

	Object->SetIterator(mapItr, orderedListItr);
}

/*******************************************************************************
*	2D描画コンポーネントリストに追加する
*******************************************************************************/
void Scene::AddDraw2DComponentList(Draw2DComponent* Component)
{
	m_Draw2DComponentList_PriorityOrdered.push_back(Component);

	// 優先度順に整列する
	SortDraw2DComponentList();
}

/*******************************************************************************
*	2D描画コンポーネントリストを優先度順に整列する
*******************************************************************************/
void Scene::SortDraw2DComponentList()
{
	// 優先度順になるよう並び変える
	m_Draw2DComponentList_PriorityOrdered.sort([](auto const& lhs, auto const& rhs) {
			return lhs->GetDrawPriority() > lhs->GetDrawPriority();
		});
}

#pragma region GetGameObject
/*******************************************************************************
*	全オブジェクト取得
*******************************************************************************/
list<GameObject*> Scene::GetAllGameObject()
{
	list<GameObject*> list;

	list = m_GameObject_Ordered;
	list.splice(list.end(), m_StaticGameObject_Ordered);

	return list;
}

/*******************************************************************************
*	オブジェクト取得(名称参照)
*******************************************************************************/
GameObject* Scene::GetGameObject(string Name)
{
	// 動的オブジェクトで名前が一致するイテレータをすべて取得
	auto range = m_GameObject.equal_range(Name);
	// １つでも見つかったら最初のイテレータの要素を返す
	if (range.first != m_GameObject.end())
	{
		return range.first->second;
	}

	// 静的オブジェクトで名前が一致するイテレータをすべて取得
	range = m_StaticGameObject.equal_range(Name);
	// １つでも見つかったら最初のイテレータの要素を返す
	if (range.first != m_StaticGameObject.end())
	{
		return range.first->second;
	}
	
	return NULL;
}

/*******************************************************************************
*	オブジェクト全取得(名称参照)
*******************************************************************************/
vector<GameObject*> Scene::GetGameObjects(string Name)
{
	vector<GameObject*> objects;

	// 動的オブジェクトで名前が一致するイテレータをすべて取得
	auto range = m_GameObject.equal_range(Name);
	// 見つかったすべての要素をリストに格納する
	if (range.first != m_GameObject.end())
	{
		for_each(range.first, range.second, [&objects](std::pair<string, GameObject*> itr)
			{ objects.push_back(itr.second); }
		);
	}

	// 静的オブジェクトで名前が一致するイテレータをすべて取得
	range = m_StaticGameObject.equal_range(Name);
	// 見つかったすべての要素をリストに格納する
	if (range.first != m_StaticGameObject.end())
	{
		for_each(range.first, range.second, [&objects](std::pair<string, GameObject*> itr)
			{ objects.push_back(itr.second); }
		);
	}

	return objects;
}

/*******************************************************************************
*	オブジェクト全取得(レイヤー参照)
*******************************************************************************/
vector<GameObject*> Scene::GetGameObjectsFromLayer(int Layer)
{
	vector<GameObject*> objects;

	// レイヤーが一致したすべてのオブジェクトを返す
	for (auto itr : m_GameObject_Ordered)
	{
		if (itr->GetLayer() & Layer) { objects.push_back(itr); }
	}
	for (auto itr : m_StaticGameObject_Ordered)
	{
		if (itr->GetLayer() & Layer) { objects.push_back(itr); }
	}

	return objects;
}

/*******************************************************************************
*	オブジェクト全取得(タグ参照)
*******************************************************************************/
vector<GameObject*> Scene::GetGameObjectsFromTag(int Tag)
{
	vector<GameObject*> objects;

	// タグが一致したすべてのオブジェクトを返す
	for (auto itr : m_GameObject_Ordered)
	{
		if (itr->GetTag() & Tag) { objects.push_back(itr); }
	}
	for (auto itr : m_StaticGameObject_Ordered)
	{
		if (itr->GetTag() & Tag) { objects.push_back(itr); }
	}

	return objects;
}
#pragma endregion

/*******************************************************************************
*	モデル・テクスチャ等のロード
*******************************************************************************/
void Scene::InitAsset()
{
	// モデル
	ModelContainer::LoadAndUnload_AllModel();

	// テクスチャ
	TextureContainer::LoadAndUnload_AllTexture();
}
