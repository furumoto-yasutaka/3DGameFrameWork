/*******************************************************************************
*
*	�^�C�g���F	�R�[���o�b�N�p�N���X	[ callbackListner.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "time.h"

/*******************************************************************************
*	���������R�[���o�b�N�N���X
*******************************************************************************/
// ���N���X(template������ƌ^���w�肷��K�v���o�Ă��܂��̂Ŏ󂯎M�Ƃ���)
class CallBackBase
{
public:
	CallBackBase() {}
	// �R�[���o�b�N�ďo
	virtual void Execute() = 0;
};

// �h���N���X
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
*	�����L��R�[���o�b�N�N���X(������1�܂�)
*******************************************************************************/
// ���N���X(template������ƌ^���w�肷��K�v���o�Ă��܂��̂Ŏ󂯎M�Ƃ���)
template<typename A>
class CallBackArgumentBase
{
public:
	CallBackArgumentBase() {}
	// �R�[���o�b�N�ďo
	virtual void Execute(A* Argument) = 0;
};

// �h���N���X
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
*	�w�莞�ԑ҂��R�[���o�b�N�N���X
*******************************************************************************/
// ���N���X(template������ƌ^���w�肷��K�v���o�Ă��܂��̂Ŏ󂯎M�Ƃ���)
class Component;

class CallBackInvokeBase
{
public:
	CallBackInvokeBase() {}
	// �R�[���o�b�N�ďo
	virtual bool CheckTime() = 0;
};

// �h���N���X
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
