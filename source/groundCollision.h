/*******************************************************************************
*
*	�^�C�g���F	�ڒn�Ǘ��X�N���v�g	[ groundCollision.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

	virtual void OnGround(Collider3D* Collider);		// �Փ˂����I�u�W�F�N�g���L�^(�R�[���o�b�N)
	virtual void NotOnGround(Collider3D* Collider);		// ���ꂽ�I�u�W�F�N�g���L�^(�R�[���o�b�N)

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	bool GetIsOnGround() { return m_IsOnGround; }
	/////////////////////////////
};
