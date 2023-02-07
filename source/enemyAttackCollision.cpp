/*******************************************************************************
*
*	�^�C�g���F	�G�l�~�[�p�U���R���W�����Ǘ��X�N���v�g	[ enemyAttackCollision.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
