/*******************************************************************************
*
*	タイトル：	コールバック用クラス	[ callbackListner.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "time.h"

/*******************************************************************************
*	引数無しコールバッククラス
*******************************************************************************/
// 基底クラス(templateがあると型を指定する必要が出てしまうので受け皿として)
class CallBackBase
{
public:
	CallBackBase() {}
	// コールバック呼出
	virtual void Execute() = 0;
};

// 派生クラス
template<class T>
class CallBackListner : public CallBackBase
{
private:
	T* m_Origin;
	void(T::* m_CallBack)();

public:
	CallBackListner(T* Origin, void(T::* CallBack)())
		: m_Origin(Origin), m_CallBack(CallBack) {}

	void Execute() override { (m_Origin->*m_CallBack)(); }
};


/*******************************************************************************
*	引数有りコールバッククラス(引数は1つまで)
*******************************************************************************/
// 基底クラス(templateがあると型を指定する必要が出てしまうので受け皿として)
template<typename A>
class CallBackArgumentBase
{
public:
	CallBackArgumentBase() {}
	// コールバック呼出
	virtual void Execute(A* Argument) = 0;
};

// 派生クラス
template<class T, typename A>
class CallBackArgumentListner : public CallBackArgumentBase<A>
{
private:
	T* m_Origin;
	void(T::* m_CallBack)(A*);

public:
	CallBackArgumentListner(T* Origin, void(T::* CallBack)(A*))
		: m_Origin(Origin), m_CallBack(CallBack) {}

	void Execute(A* Argument) override { (m_Origin->*m_CallBack)(Argument); }
};


/*******************************************************************************
*	指定時間待ちコールバッククラス
*******************************************************************************/
// 基底クラス(templateがあると型を指定する必要が出てしまうので受け皿として)
class Component;

class CallBackInvokeBase
{
public:
	CallBackInvokeBase() {}
	// コールバック呼出
	virtual bool CheckTime() = 0;
};

// 派生クラス
template<class T>
class CallBackInvoke : public CallBackInvokeBase
{
private:
	T* m_Origin;
	void(T::* m_CallBack)();
	float m_Time;

public:
	CallBackInvoke(Component* Origin, void(T::* CallBack)(), float Time)
		: m_Origin(reinterpret_cast<T*>(Origin)), m_CallBack(CallBack), m_Time(Time) {}

	bool CheckTime() override
	{
		if (m_Time <= 0.0f)
		{
			(m_Origin->*m_CallBack)();
			return true;
		}
		else
		{
			m_Time -= Time::GetDeltaTimeSec();
			return false;
		}
	}
};
