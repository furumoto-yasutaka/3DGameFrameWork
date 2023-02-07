/*******************************************************************************
*
*	�^�C�g���F	Invoke���؃X�N���v�g	[ testInvoke.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "testInvoke.h"
#include "gameObject.h"
#include "componentDebug_TestInvoke.h"

void TestInvoke::Init()
{
	SetInvoke(&TestInvoke::Reset, m_Interval);

#ifdef _DEBUG
	m_ComponentDebug = new ComponentDebug_TestInvoke(this);
#endif
}

void TestInvoke::Update()
{
	m_AttachObject->m_LocalPosition.y -= m_Speed;
}

void TestInvoke::Reset()
{
	m_AttachObject->m_LocalPosition.y = 0.0f;
	SetInvoke(&TestInvoke::Reset, m_Interval);
}

#ifdef _DEBUG
ComponentDebugInfo* TestInvoke::GetComponentDebugInfo()
{
	return m_ComponentDebug;
}
#endif
