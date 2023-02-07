/*******************************************************************************
*
*	タイトル：	エネミー用探知管理スクリプト	[ enemySearchCollision.h ]
*
*	作成者：	古本 泰隆
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
