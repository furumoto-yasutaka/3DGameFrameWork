/*******************************************************************************
*
*	タイトル：	接触オブジェクト管理スクリプト	[ collisionContactRecorder.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"
#include "gameObject.h"
#include "collider3d.h"

template<class T>
class CollisionContactRecorder : public ScriptComponent
{
protected:
	T* m_Collider = NULL;

	int m_TargetTag = 0;
	bool m_IsContact = false;
	list<GameObject*> m_OnContactList;

	bool m_IsMatchTag = false;
	bool m_IsPush = false;
	bool m_IsRemove = false;

	bool m_IsInheritance = false;

public:
	CollisionContactRecorder<T>(GameObject* AttachObject)
		: ScriptComponent(AttachObject),
		m_IsInheritance(true)
	{}

	virtual void Init(int Tag)
	{
		m_TargetTag = Tag;
	}
	virtual void LateInit() override
	{
		m_Collider = m_AttachObject->GetComponent<T>();
		m_Collider->SetOnContactEnter(this, &CollisionContactRecorder<T>::ContactEnter);
		m_Collider->SetOnContactExit(this, &CollisionContactRecorder<T>::ContactExit);
	}
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}

	// 衝突したオブジェクトを記録(コールバック)
	virtual void ContactEnter(Collider3D* Collider)
	{
		m_IsMatchTag = Collider->GetAttachObject()->GetTag() & m_TargetTag;
		if (m_IsMatchTag)
		{
			auto itr = find(m_OnContactList.begin(), m_OnContactList.end(), Collider->GetAttachObject());
			m_IsRemove = itr == m_OnContactList.end();
			if (m_IsRemove)
			{
				m_OnContactList.push_back(Collider->GetAttachObject());
				if (m_OnContactList.size() > 0)
				{
					m_IsContact = true;
				}
			}
		}

		if (!m_IsInheritance)
		{
			ResetEnterFlag();
		}
	}
	// 離れたオブジェクトを記録(コールバック)
	virtual void ContactExit(Collider3D* Collider)
	{
		m_IsMatchTag = Collider->GetAttachObject()->GetTag() & m_TargetTag;
		if (m_IsMatchTag)
		{
			auto itr = find(m_OnContactList.begin(), m_OnContactList.end(), Collider->GetAttachObject());
			m_IsRemove = itr != m_OnContactList.end();
			if (m_IsRemove)
			{
				m_OnContactList.remove(Collider->GetAttachObject());
				if (m_OnContactList.size() == 0)
				{
					m_IsContact = false;
				}
			}
		}

		if (!m_IsInheritance)
		{
			ResetExitFlag();
		}
	}

	virtual void ResetEnterFlag()
	{
		m_IsMatchTag = false;
		m_IsPush = false;
	}

	virtual void ResetExitFlag()
	{
		m_IsMatchTag = false;
		m_IsRemove = false;
	}

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	bool GetIsContact() { return m_IsContact; }
	list<GameObject*> GetOnContactList() { return m_OnContactList; }
	/////////////////////////////
};
