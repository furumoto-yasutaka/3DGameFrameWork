/*******************************************************************************
*
*	�^�C�g���F	�G�l�~�[�p�U���R���W�����Ǘ��X�N���v�g	[ enemyAttackCollision.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

	virtual void ContactPlayer(Collider3D* Collider);	// �Փ˂����I�u�W�F�N�g���L�^(�R�[���o�b�N)
	virtual void MissPlayer(Collider3D* Collider);	// ���ꂽ�I�u�W�F�N�g���L�^(�R�[���o�b�N)

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	bool GetIsContactPlayer() { return m_IsContactPlayer; }
	/////////////////////////////
};