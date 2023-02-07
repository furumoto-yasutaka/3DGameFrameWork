/*******************************************************************************
*
*	タイトル：	コンポーネント基底クラス	[ component.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "callbackListner.h"

#include <list>

class GameObject;
class ComponentDebugInfo;

class Component
{
public:
	// コンポーネントの分類
	enum class ProcGroup
	{
		System = 0,	// 描画を伴わないもの
		Script,		// スクリプト
		Draw3D,		// 3D描画を伴うもの
		Draw2D,		// 2D描画を伴うもの
		Physics,	// 物理
		Length,
	};

protected:
	GameObject* m_AttachObject;						// アタッチ先オブジェクト
	ProcGroup	m_ProcGroup = ProcGroup::System;	// 処理グループ
	bool		m_Active = true;					// アクティブフラグ
	bool		m_Destroy = false;					// 削除フラグ

public:
	Component() = delete;
	Component(GameObject* AttachObject) : m_AttachObject(AttachObject) {}

	virtual void LateInit() {}
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() {}
	virtual void Draw() = 0;

	// 自身の削除を予約
	virtual void SetDestroy() { m_Destroy = true; }

	// 削除処理
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	GameObject* GetAttachObject() { return m_AttachObject; }

	ProcGroup GetProcGroup() { return m_ProcGroup; }

	bool GetActive() { return m_Active; }
	void SetActive(bool value) { m_Active = value; }
	/////////////////////////////

#ifdef _DEBUG
	// デバッグ情報表示用
	virtual ComponentDebugInfo* GetComponentDebugInfo() { return NULL; }
#endif
};
