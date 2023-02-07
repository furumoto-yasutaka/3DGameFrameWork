/*******************************************************************************
*
*	�^�C�g���F	�v���C���[�ڒn�Ǘ��X�N���v�g	[ collisionContactRecorder_PlayerAttack.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

		// ���̉�����܂ł͐e�N���X�̌^���s���ĂȂ��߂�
		// �r���h���̖��O�������ł����G���[�ɂȂ�̂�
		// this��t���Ė��O���������̉����ɍs���悤�ɂ���
		m_Manager = this->m_AttachObject->GetRoot()->GetComponent<PlayerManager>();
	}

	// �Փ˂����I�u�W�F�N�g���L�^(�R�[���o�b�N)
	void ContactEnter(Collider3D* Collider) override
	{
		CollisionContactRecorder<T>::ContactEnter(Collider);

		if (this->m_IsMatchTag)
		{
			// �S�Ă̓G��Manager�̎擾�����݂�
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
	//�@�����@�A�N�Z�T�@�����@//
	void SetManager(PlayerManager* Manager) { m_Manager = Manager; }
	/////////////////////////////
};
