/*******************************************************************************
*
*	タイトル：	デモ用オブジェクト移動スクリプト	[ testMove.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "testMove.h"
#include "gameObject.h"

void TestMove::Init(D3DXVECTOR3 MoveRange)
{
	m_FirstPos = m_AttachObject->m_LocalPosition;
	m_MoveRange = MoveRange;
}

void TestMove::Update()
{
	m_Time += Time::GetDeltaTimeSec();

	m_AttachObject->m_LocalPosition = m_FirstPos + m_MoveRange * sinf(m_Time);
}
