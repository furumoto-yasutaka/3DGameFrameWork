/*******************************************************************************
*
*	�^�C�g���F	�f���p�I�u�W�F�N�g�ړ��X�N���v�g	[ testMove.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
