/*******************************************************************************
*
*	タイトル：	エネミー用攻撃コリジョン管理スクリプト	[ enemyAttackCollision.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "enemyAttackCollision.h"
#include "gameObject.h"
#include "obbCollider3d.h"

void EnemyAttackCollision::LateInit()
{
	m_AttackCollider = m_AttachObject->GetComponent<OBBCollider3D>();
	m_AttackCollider->SetOnContactEnter(this, &EnemyAttackCollision::ContactPlayer);
	m_AttackCollider->SetOnContactExit(this, &EnemyAttackCollision::MissPlayer);
}

void EnemyAttackCollision::ContactPlayer(Collider3D* Collider)
{
	if (Collider->GetAttachObject()->GetTag() & (int)Scene::ObjTag::Player)
	{
		m_IsContactPlayer = true;
	}
}

void EnemyAttackCollision::MissPlayer(Collider3D* Collider)
{
	if (Collider->GetAttachObject()->GetTag() & (int)Scene::ObjTag::Player)
	{
		m_IsContactPlayer = false;
	}
}
