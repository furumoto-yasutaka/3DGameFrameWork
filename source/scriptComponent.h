/*******************************************************************************
*
*	タイトル：	スクリプト系コンポーネント基底クラス	[ scriptComponent.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "component.h"

class ScriptComponent : public Component
{
protected:
	list<CallBackInvokeBase*> m_InvokeList;	// 指定時間待ちコールバックリスト

public:
	ScriptComponent(GameObject* AttachObject);

	void Uninit() override { DestroyInvoke(); }
	void LateUpdate() override { CheckInvoke(); }
	
	template<class T>
	void SetInvoke(void(T::* Function)(), float Time)
	{
		m_InvokeList.push_back(new CallBackInvoke<T>(this, Function, Time));
	}
	void DestroyInvoke()
	{
		auto itr = m_InvokeList.begin();
		while (itr != m_InvokeList.end())
		{
			delete (*itr);
			itr = m_InvokeList.erase(itr);
		}
	}
	void CheckInvoke()
	{
		auto itr = m_InvokeList.begin();
		while (itr != m_InvokeList.end())
		{
			if ((*itr)->CheckTime())
			{
				delete (*itr);
				itr = m_InvokeList.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
};
