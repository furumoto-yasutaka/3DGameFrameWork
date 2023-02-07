/*******************************************************************************
*
*	�^�C�g���F	�G�l�~�[�p�W�����v���f�R���W�����Ǘ��X�N���v�g	[ enemyJumpCollision.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

	virtual void FindPlayer(Collider3D* Collider);	// �Փ˂����I�u�W�F�N�g���L�^(�R�[���o�b�N)
	virtual void MissPlayer(Collider3D* Collider);	// ���ꂽ�I�u�W�F�N�g���L�^(�R�[���o�b�N)

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	bool GetIsFindPlayer() { return m_IsFindPlayer; }
	/////////////////////////////
};
