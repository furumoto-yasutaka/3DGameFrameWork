/*******************************************************************************
*
*	�^�C�g���F	�X�N���v�g�n�R���|�[�l���g���N���X	[ scriptComponent.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "component.h"

class ScriptComponent : public Component
{
protected:
	list<CallBackInvokeBase*> m_InvokeList;	// �w�莞�ԑ҂��R�[���o�b�N���X�g

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
