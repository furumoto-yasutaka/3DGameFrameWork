/*******************************************************************************
*
*	タイトル：	エネミー用攻撃コリジョン管理スクリプト	[ enemyAttackCollision.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class Collider3D;
class OBBCollider3D;

class EnemyAttackCollision : public ScriptComponent
{
private:
	OBBCollider3D* m_AttackCollider = NULL;

	bool m_IsContactPlayer = false;

public:
	EnemyAttackCollision(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init() {}
	void LateInit() override;
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}

	virtual void ContactPlayer(Collider3D* Collider);	// 衝突したオブジェクトを記録(コールバック)
	virtual void MissPlayer(Collider3D* Collider);	// 離れたオブジェクトを記録(コールバック)

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	bool GetIsContactPlayer() { return m_IsContactPlayer; }
	/////////////////////////////
};