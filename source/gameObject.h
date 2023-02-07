/*******************************************************************************
*
*	タイトル：	ゲームオブジェクトクラス	[ gameObject.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "component.h"
#include "manager.h"

#include <unordered_map>
#include <list>
#include <vector>
#include <typeinfo>
#include <string>

class GameObject
{
public:
	// 親オブジェクト設定時の子に対するオプション
	enum class SetParentOption
	{
		Nothing		= 0,
		KeepPos		= 1 << 0,		// 座標を維持
		KeepScale	= 1 << 1,		// 拡縮を維持
		All			= (1 << 2) - 1,
	};

private:
	unordered_multimap<string, GameObject*>::iterator m_MapIterator;	// マップイテレーター
	list<GameObject*>::iterator m_OrderedListIterator;					// リストイテレーター

	// 0：描画を伴わないもの
	// 1：スクリプト
	// 2：3D描画を伴うもの
	// 3：2D描画を伴うもの
	// 4：物理
	list<Component*>	m_ComponentList[(int)Component::ProcGroup::Length];	// コンポーネントリスト
	GameObject*			m_Parent = NULL;		// 親オブジェクト
	list<GameObject*>	m_Child;				// 子オブジェクト

	bool				m_IsActive = true;		// アクティブフラグ
	bool				m_IsDestroy = false;	// 削除フラグ
	bool				m_IsStatic = false;		// 静的フラグ
	string				m_Name;					// オブジェクト名
	int					m_Layer;				// コリジョンレイヤー
	int					m_Tag;					// オブジェクトタグ
#ifdef _DEBUG
	static inline ID3D11Buffer* m_VertexBuffer = NULL;			// 頂点バッファ
	static inline ID3D11VertexShader* m_VertexShader = NULL;	// 頂点シェーダー
	static inline ID3D11PixelShader* m_PixelShader = NULL;		// ピクセルシェーダー
	static inline ID3D11InputLayout* m_VertexLayout = NULL;		// 入力レイアウト
#endif
public:	
	D3DXVECTOR3			m_LocalPosition;		// 座標
	D3DXQUATERNION		m_LocalRotation;		// 回転
	D3DXVECTOR3			m_LocalScale;			// サイズ

public:
	void Init(string Name, int Layer, int Tag,
		unordered_multimap<string, GameObject*>::iterator MapItr,
		list<GameObject*>::iterator OrderedListItr);
	void LateInit();
	void Uninit();
	void Update(int Group);
	void LateUpdate(int Group);
	void Draw(int Group);

	// コンポーネントの削除確認
	void CheckComponentDestroy();

	// マトリクスを取得
	D3DXMATRIX GetMatrix();

	// 正面方向の単位ベクトルを取得
	D3DXVECTOR3 GetForward();

	// 上方向の単位ベクトルを取得
	D3DXVECTOR3 GetUp();

	// 右方向の単位ベクトルを取得
	D3DXVECTOR3 GetRight();

	// 自身とその子オブジェクトの削除を予約
	void SetDestroy();

	// 削除処理
	bool Destroy();

	/////////////////////////////
	//　↓↓　親子関係　↓↓　//
	
	// 自身のローカルマトリクスの原点におけるワールドマトリクス(親のワールドマトリクス)取得
	D3DXMATRIX GetLocalMatrixOrigin();
	// ワールドマトリクス取得
	D3DXMATRIX GetWorldMatrix(D3DXMATRIX Matrix = Math::GetMatrixIdentity());

	// 自身のローカル座標の原点におけるワールド座標(親のワールド座標)取得
	D3DXVECTOR3 GetLocalPositionOrigin();
	// ワールド座標取得
	D3DXVECTOR3 GetWorldPosition(D3DXVECTOR3 Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// ワールド座標設定
	void SetWorldPosition(D3DXVECTOR3 Position);

	// 自身のローカルローテーションの原点におけるワールドローテーション(親のワールドローテーション)取得
	D3DXQUATERNION GetLocalRotationOrigin();
	// ワールドローテーション取得
	D3DXQUATERNION GetWorldRotation(D3DXQUATERNION Rotation = Math::GetQuaternionIdentity());
	// ワールドローテーション設定
	void SetWorldRotation(D3DXQUATERNION Rotation);

	// 自身のローカルスケールの原点におけるワールドスケール(親のワールドスケール)取得
	D3DXVECTOR3 GetLocalScaleOrigin();
	// ワールドスケール取得
	D3DXVECTOR3 GetWorldScale(D3DXVECTOR3 Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	// ワールドスケール設定
	void SetWorldScale(D3DXVECTOR3 Scale);
	/////////////////////////////

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	unordered_multimap<string, GameObject*>::iterator GetMapIterator() { return m_MapIterator; }
	list<GameObject*>::iterator GetOrderedListIterator() { return m_OrderedListIterator; }
	void SetIterator(unordered_multimap<string, GameObject*>::iterator MapItr,
		list<GameObject*>::iterator OrderedListItr);

	list<Component*> GetComponentAll();

	GameObject* GetRoot();

	GameObject* GetParent() { return m_Parent; }
	void SetParent(GameObject* Parent,
		int RemoveOption = (int)SetParentOption::Nothing,
		int SetOption = (int)SetParentOption::Nothing);

	list<GameObject*> GetChildList() { return m_Child; }
	GameObject* GetChild(int index);

	bool GetActive();
	void SetActive(bool Value) { m_IsActive = Value; }

	bool GetIsDestroy() { return m_IsDestroy; }

	bool GetStatic() { return m_IsStatic; }
	void SetStatic(bool Value);

	string GetName() { return m_Name; }
	void SetName(string NewName);

	int GetLayer() { return m_Layer; }
	void AddLayer(int Layer) { m_Layer |= Layer; }

	int GetTag() { return m_Tag; }
	void AddTag(int Tag) { m_Tag |= Tag; }
	/////////////////////////////

private:
	void CheckRemoveOption(int Option, GameObject* Parent);
	void CheckSetOption(int Option, GameObject* Parent);

	/////////////////////////////////
	//　↓↓　基本呼出禁止　↓↓　//
public:
	// 子オブジェクトを追加　※基本呼出禁止
	void AddChild(GameObject* Child) { m_Child.push_back(Child); }
	// 子オブジェクトを削除　※基本呼出禁止
	void RemoveChild(GameObject* Child) { m_Child.remove(Child); }
	/////////////////////////////////


	/*******************************************************************************
	*	コンポーネント追加
	*******************************************************************************/
	template<class T>
	T* AddComponent()
	{
		T* component = DBG_NEW T(this);
		m_ComponentList[(int)component->GetProcGroup()].push_back(component);
		return component;
	}

	/*******************************************************************************
	*	コンポーネント取得(クラス名参照)
	*******************************************************************************/
	template<class T>
	T* GetComponent()
	{
		for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
		{
			for (Component* c : m_ComponentList[i])
			{
				if (typeid(*c) == typeid(T))
				{
					return (T*)c;
				}
			}
		}
		return NULL;
	}

	/*******************************************************************************
	*	コンポーネント全取得(クラス名参照)
	*******************************************************************************/
	template<class T>
	vector<T*> GetComponents()
	{
		vector<T*> components;
		for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
		{
			for (Component* c : m_ComponentList[i])
			{
				if (typeid(*c) == typeid(T))
				{
					components.push_back(c);
				}
			}
		}
		return components;
	}

#ifdef _DEBUG
private:
	void InitDebug();
	void UninitDebug();
	void CreateVertex(VERTEX_3D* Vertex);
public:
	void DrawDebug();
#endif
};
