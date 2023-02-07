/*******************************************************************************
*
*	タイトル：	接地管理スクリプト	[ groundCollision.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class Collider3D;
class AABBCollider3D;

class GroundCollision : public ScriptComponent
{
protected:
	AABBCollider3D* m_GroundCollider = NULL;

	bool m_IsOnGround = false;
	list<GameObject*> m_OnGroundList;

public:
	GroundCollision(GameObject* AttachObject) : ScriptComponent(AttachObject) {}

	void Init();
	void LateInit() override;
	void Uninit() override {}
	void Update() override {}
	void Draw() override {}

	virtual void OnGround(Collider3D* Collider);		// 衝突したオブジェクトを記録(コールバック)
	virtual void NotOnGround(Collider3D* Collider);		// 離れたオブジェクトを記録(コールバック)

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	bool GetIsOnGround() { return m_IsOnGround; }
	/////////////////////////////
};
