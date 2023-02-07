/*******************************************************************************
*
*	タイトル：	エネミー用ジャンプ判断コリジョン管理スクリプト	[ enemyJumpCollision.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class Collider3D;
class OBBCollider3D;

class EnemyJumpCollision
{
private:
	OBBCollider3D* m_SearchCollider = NULL;

	bool m_IsContactPlatform = false;

public:
	EnemySearchCollision(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init() {}
	void LateInit() override;
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}

	virtual void FindPlayer(Collider3D* Collider);	// 衝突したオブジェクトを記録(コールバック)
	virtual void MissPlayer(Collider3D* Collider);	// 離れたオブジェクトを記録(コールバック)

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	bool GetIsFindPlayer() { return m_IsFindPlayer; }
	/////////////////////////////
};
