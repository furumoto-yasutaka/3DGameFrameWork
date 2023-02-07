/*******************************************************************************
*
*	�^�C�g���F	�G�l�~�[�p�T�m�R���W�����Ǘ��X�N���v�g	[ enemySearchCollision.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "scriptComponent.h"

class Collider3D;
class OBBCollider3D;

class EnemySearchCollision : public ScriptComponent
{
private:
	OBBCollider3D* m_SearchCollider = NULL;

	bool m_IsFindPlayer = false;

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
