/*******************************************************************************
*
*	タイトル：	プレイヤー接地管理スクリプト	[ collisionContactRecorder_PlayerGround.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "collisionContactRecorder.h"
#include "playerManager.h"

template<class T>
class CollisionContactRecorder_PlayerGround : public CollisionContactRecorder<T>
{
private:
	PlayerManager* m_Manager = NULL;

public:
	CollisionContactRecorder_PlayerGround(GameObject* AttachObject) :
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

		if (this->m_IsContact)
		{
			m_Manager->GetParameter()->m_IsCanAirAvoid = true;
		}

		this->ResetEnterFlag();
	}

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	void SetManager(PlayerManager* Manager) { m_Manager = Manager; }
	/////////////////////////////
};
