/*******************************************************************************
*
*	タイトル：	プレイヤー接地管理スクリプト	[ collisionContactRecorder_PlayerAttack.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "collisionContactRecorder.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "playerActionStateBase.h"

#include "eggEnemyManager.h"

template<class T>
class CollisionContactRecorder_PlayerAttack : public CollisionContactRecorder<T>
{
private:
	PlayerManager* m_Manager = NULL;

public:
	CollisionContactRecorder_PlayerAttack(GameObject* AttachObject) :
		CollisionContactRecorder<T>(AttachObject)
	{}

	void LateInit() override
	{
		CollisionContactRecorder<T>::LateInit();

		// 実体化するまでは親クラスの型が不明瞭なために
		// ビルド時の名前解決ができずエラーになるので
		// thisを付けて名前解決を実体化時に行うようにする
		m_Manager = this->m_AttachObject->GetRoot()->GetComponent<PlayerManager>();
	}

	// 衝突したオブジェクトを記録(コールバック)
	void ContactEnter(Collider3D* Collider) override
	{
		CollisionContactRecorder<T>::ContactEnter(Collider);

		if (this->m_IsMatchTag)
		{
			// 全ての敵のManagerの取得を試みる
			EnemyManager* enemy = Collider->GetAttachObject()->GetComponent<EggEnemyManager>();

			float DistanceRate = 0.0f;
			switch (m_Manager->GetActionState()->GetStateId())
			{
				using enum PlayerManager::ActionStateId;
			case ShortRoll_Left:
			case ShortRoll_Right:
				enemy->ShortRollDamage();
				break;
			case Roll_Left:
			case Roll_Right:
				DistanceRate = CalcDistanceRate(enemy);
				enemy->RollDamage(DistanceRate);
				break;
			case LongRoll_Left:
			case LongRoll_Right:
				enemy->LongRollDamage();
				break;
			default: break;
			}
		}

		this->ResetEnterFlag();
	}

	float CalcDistanceRate(EnemyManager* Enemy)
	{
		D3DXVECTOR3 playerPos = this->m_AttachObject->GetRoot()->m_LocalPosition;
		D3DXVECTOR3 enemyPos = Enemy->GetAttachObject()->GetWorldPosition();
		D3DXVECTOR3 distanceVec = enemyPos - playerPos;

		return D3DXVec3Length(&distanceVec) * 0.2f;
	}

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	void SetManager(PlayerManager* Manager) { m_Manager = Manager; }
	/////////////////////////////
};
