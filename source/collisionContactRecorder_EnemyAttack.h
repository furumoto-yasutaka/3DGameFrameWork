/*******************************************************************************
*
*	タイトル：	エネミー攻撃判定管理スクリプト	[ collisionContactRecorder_EnemyAttack.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "collisionContactRecorder.h"
#include "playerManager.h"
#include "enemyManager.h"

template<class T>
class CollisionContactRecorder_EnemyAttack : public CollisionContactRecorder<T>
{
private:
	EnemyManager* m_Manager = NULL;
	
	int m_Damage = 0;

	bool m_IsAttacked = false;

public:
	CollisionContactRecorder_EnemyAttack(GameObject* AttachObject)
		: CollisionContactRecorder<T>(AttachObject),
		m_Damage(0)
	{}

	void LateInit() override
	{
		CollisionContactRecorder<T>::LateInit();

		// 実体化するまでは親クラスの型が不明瞭なために
		// ビルド時の名前解決ができずエラーになるので
		// thisを付けて名前解決を実体化時に行うようにする
		m_Manager = this->m_AttachObject->GetRoot()->GetComponent<EnemyManager>();
	}

	// 衝突したオブジェクトを記録(コールバック)
	void ContactEnter(Collider3D* Collider) override
	{
		CollisionContactRecorder<T>::ContactEnter(Collider);

		if (this->m_IsMatchTag)
		{
			if (!m_IsAttacked)
			{
				PlayerManager* player = Collider->GetAttachObject()->GetComponent<PlayerManager>();
				player->Damage(m_Damage);

				m_IsAttacked = true;
			}
		}

		this->ResetEnterFlag();
	}

	void EndAttack()
	{
		m_IsAttacked = false;
	}

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	void SetManager(PlayerManager* Manager) { m_Manager = Manager; }
	/////////////////////////////
};
