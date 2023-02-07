/*******************************************************************************
*
*	�^�C�g���F	�G�l�~�[�p�T�m�Ǘ��X�N���v�g	[ enemySearchCollision.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "enemySearchCollision.h"
#include "gameObject.h"
#include "obbCollider3d.h"

void EnemySearchCollision::LateInit()
{
	m_SearchCollider = m_AttachObject->GetComponent<OBBCollider3D>();
	m_SearchCollider->SetOnContactEnter(this, &EnemySearchCollision::FindPlayer);
	m_SearchCollider->SetOnContactExit(this, &EnemySearchCollision::MissPlayer);
}

void EnemySearchCollision::FindPlayer(Collider3D* Collider)
{
	if (Collider->GetAttachObject()->GetTag() & (int)Scene::ObjTag::Player)
	{
		m_IsFindPlayer = true;
	}
}

void EnemySearchCollision::MissPlayer(Collider3D* Collider)
{
	if (Collider->GetAttachObject()->GetTag() & (int)Scene::ObjTag::Player)
	{
		m_IsFindPlayer = false;
	}
}
