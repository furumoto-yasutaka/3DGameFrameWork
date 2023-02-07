/*******************************************************************************
*
*	�^�C�g���F	�ڒn�Ǘ��X�N���v�g	[ groundCollision.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "groundCollision.h"
#include "gameObject.h"
#include "aabbCollider3d.h"
#include "playerManager.h"

void GroundCollision::Init()
{

}

void GroundCollision::LateInit()
{
	m_GroundCollider = m_AttachObject->GetComponent<AABBCollider3D>();
	m_GroundCollider->SetOnContactEnter(this, &GroundCollision::OnGround);
	m_GroundCollider->SetOnContactExit(this, &GroundCollision::NotOnGround);
}

void GroundCollision::OnGround(Collider3D* Collider)
{
	if (Collider->GetAttachObject()->GetTag() & (int)Scene::ObjTag::Platform)
	{
		auto itr = find(m_OnGroundList.begin(), m_OnGroundList.end(), Collider->GetAttachObject());
		if (itr == m_OnGroundList.end())
		{
			m_OnGroundList.push_back(Collider->GetAttachObject());
			if (m_OnGroundList.size() > 0)
			{
				m_IsOnGround = true;
			}
		}
	}
}

void GroundCollision::NotOnGround(Collider3D* Collider)
{
	if (Collider->GetAttachObject()->GetTag() & (int)Scene::ObjTag::Platform)
	{
		auto itr = find(m_OnGroundList.begin(), m_OnGroundList.end(), Collider->GetAttachObject());
		if (itr != m_OnGroundList.end())
		{
			m_OnGroundList.remove(Collider->GetAttachObject());
			if (m_OnGroundList.size() == 0)
			{
				m_IsOnGround = false;
			}
		}
	}
}
