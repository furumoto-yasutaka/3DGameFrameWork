/*******************************************************************************
*
*	タイトル：	シーン基底クラス	[ scene.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <unordered_map>
#include <list>
#include <vector>
#include <string>

class Camera;
class GameObject;
class Draw2DComponent;

class Scene
{
public:
	// シーン別ビットフラグ
	enum class SceneTag
	{
		Nothing					= 0,			// 無
		Demo_Invoke				= 1 << 0,
		Demo_CollisionSplit0	= 1 << 1,
		Demo_CollisionSplit1	= 1 << 2,
		Demo_Parent				= 1 << 3,
		Test					= 1 << 4,
		Everything				= (1 << 5) - 1,	// 全て
	};
	// コリジョンレイヤー(ビットフラグ)
	enum class ObjLayer
	{
		Default = 1 << 0,
	};
	// オブジェクトタグ(ビットフラグ)
	enum class ObjTag
	{
		Default			= 0,
		Player			= 1 << 0,
		Platform		= 1 << 1,
		Enemy			= 1 << 2,
		Everything		= (1 << 3) - 1,
	};
	static inline const bool CollisionFlag[3][3]
	{
		//Enemy		Platform	Player
		{ true,		true,		false	},	// Player
		{ true,		true,		true	},	// Platform
		{ true,		true,		true	},	// Enemy
	};

protected:
	unordered_multimap<string, GameObject*>			m_GameObject;				// 動的オブジェクトリスト
	static inline unordered_multimap<string, GameObject*>	m_StaticGameObject;	// 静的オブジェクトリスト
	SceneTag										m_Tag;						// 自身のシーンを表すタグ
	Camera*											m_ActiveCamera = NULL;		// 現在有効になっているカメラ
	
	list<GameObject*>								m_GameObject_Ordered;		// 動的オブジェクトリスト(優先度順)
	static inline list<GameObject*>					m_StaticGameObject_Ordered;	// 静的オブジェクトリスト(優先度順)
	
	list<Draw2DComponent*> m_Draw2DComponentList_PriorityOrdered;				// 2D描画の描画順を表すリスト

public:
	virtual void Init();
	void LateInit();
	void Uninit();
	virtual void Update();
	void Draw();

	// オブジェクト削除確認
	void CheckObjectDestroy();

	// オブジェクトをシーンに追加
	GameObject* AddGameObject(string Name, int Layer = (int)ObjLayer::Default, int Tag = (int)ObjTag::Default, bool IsStatic = false);

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//

	// 全オブジェクト取得
	list<GameObject*> GetAllGameObject();
	// オブジェクト取得(名称参照)
	GameObject* GetGameObject(string Name);
	// オブジェクト全取得(名称参照)
	vector<GameObject*> GetGameObjects(string Name);
	// オブジェクト全取得(レイヤー参照)
	vector<GameObject*> GetGameObjectsFromLayer(int Layer);
	// オブジェクト全取得(タグ参照)
	vector<GameObject*> GetGameObjectsFromTag(int Tag);

	int GetTag() { return (int)m_Tag; }

	Camera* GetActiveCamera() { return m_ActiveCamera; }
	void SetActiveCamera(Camera* ActiveCamera) { m_ActiveCamera = ActiveCamera; }
	/////////////////////////////


	/////////////////////////////////
	//　↓↓　基本呼出禁止　↓↓　//

	// 静的オブジェクトに変更する
	void SetStatic(GameObject* Object);

	// 動的オブジェクトに変更する
	void SetDynamic(GameObject* Object);

	// オブジェクトの名前(キー)を変更する
	void SetObjectName(GameObject* Object, string NewName);

	// 2D描画コンポーネントリストに追加する
	void AddDraw2DComponentList(Draw2DComponent* Component);

	// 2D描画コンポーネントリストを優先度順に整列する
	void SortDraw2DComponentList();
	/////////////////////////////////
private:
	// モデル・テクスチャ等のロード
	void InitAsset();
};
