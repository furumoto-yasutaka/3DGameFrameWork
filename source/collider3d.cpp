/*******************************************************************************
*
*	タイトル：	3Dコリジョン基底クラス	[ collider3d.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "collider3d.h"
#include "collision3dManager.h"
#include "treeCell.h"
#include "gameObject.h"

void Collider3D::Init(D3DXVECTOR3 Offset, bool IsTrigger, bool IsStatic)
{
	m_Offset = Offset;
	m_IsTrigger = IsTrigger;
	m_IsStatic = IsStatic;

	m_ThisCellData = Collision3DManager::Regist(this);
}

void Collider3D::Uninit()
{
	m_ThisCellData->Remove();
	Collision3DManager::RemoveTreeCellData(m_ThisCellData);
}

void Collider3D::Collision(Collider3D* Collider)
{
	switch (Collider->GetId())
	{
		using enum ColliderId;
	case AABB:
		CollisionAABB(reinterpret_cast<AABBCollider3D*>(Collider));
		break;
	case OBB:
		CollisionOBB(reinterpret_cast<OBBCollider3D*>(Collider));
		break;
	case Sphere:
		CollisionSphere(reinterpret_cast<SphereCollider3D*>(Collider));
		break;
	case Capsule:
		CollisionCapsule(reinterpret_cast<CapsuleCollider3D*>(Collider));
		break;
	}

#ifdef _DEBUG
	Collision3DManager::AddCollisionCount();
#endif
}

D3DXVECTOR3 Collider3D::GetColliderWorldPos()
{
	D3DXMATRIX result, world, offset;
	world = m_AttachObject->GetWorldMatrix();
	D3DXMatrixTranslation(&offset, m_Offset.x, m_Offset.y, m_Offset.z);
	result = offset * world;

	return { result._41, result._42, result._43 };
}

void Collider3D::CallOnContactEnter(Collider3D* Collider)
{
	if (m_OnContactEnter)
	{
		m_OnContactEnter->Execute(Collider);
	}
}
void Collider3D::CallOnContactStay(Collider3D* Collider)
{
	if (m_OnContactStay)
	{
		m_OnContactStay->Execute(Collider);
	}
}
void Collider3D::CallOnContactExit(Collider3D* Collider)
{
	if (m_OnContactExit)
	{
		m_OnContactExit->Execute(Collider);
	}
}

void Collider3D::AddContactList(Collider3D* Collider)
{
	// 自分がトリガーモードではなく、相手はトリガーモードの場合は何もしない
	if (!m_IsTrigger && Collider->GetIsTrigger())
	{
		return;
	}
	else
	{
		m_ContactList.push_back(Collider);
	}
}

void Collider3D::RemoveRemainElement(Collider3D* Collider)
{
	m_RemainList.remove(Collider);
}

void Collider3D::CheckCallBack()
{
	auto cItr = m_ContactList.begin();

	while (cItr != m_ContactList.end())
	{
		if ((*cItr)->GetIsTrigger() && !m_IsTrigger)
		{
			cItr = m_ContactList.erase(cItr);
			continue;
		}

		auto findItr = find(m_RemainList.begin(), m_RemainList.end(), (*cItr));
		if (findItr != m_RemainList.end())
		{
			CallOnContactStay((*cItr));
			m_RemainList.erase(findItr);
		}
		else
		{
			CallOnContactEnter((*cItr));
		}

		cItr++;
	}

	for (Collider3D* c : m_RemainList)
	{
		CallOnContactExit(c);
	}

	m_RemainList = m_ContactList;
	m_ContactList.clear();
}

float Collider3D::CalcDirectionVectorSeparateAxisLength(
	D3DXVECTOR3 A_DirVec, D3DXVECTOR3 A_DirVecNormal,
	D3DXVECTOR3 B_DirVecRight, D3DXVECTOR3 B_DirVecUp, D3DXVECTOR3 B_DirVecForward,
	D3DXVECTOR3 Distance)
{
	float r1 = D3DXVec3Length(&A_DirVec);
	float r2 = LenSegOnSeparateAxis(&A_DirVecNormal,
		&B_DirVecRight, &B_DirVecUp, &B_DirVecForward);
	float length = fabs(D3DXVec3Dot(&Distance, &A_DirVecNormal));
	float bite = length - (r1 + r2);

	return bite;
}

float Collider3D::CalcCrossSeparateAxisLength(D3DXVECTOR3 Cross,
	D3DXVECTOR3 A_DirVec1, D3DXVECTOR3 A_DirVec2,
	D3DXVECTOR3 B_DirVec1, D3DXVECTOR3 B_DirVec2,
	D3DXVECTOR3 Distance)
{
	float r1 = LenSegOnSeparateAxis(&Cross, &A_DirVec1, &A_DirVec2);
	float r2 = LenSegOnSeparateAxis(&Cross, &B_DirVec1, &B_DirVec2);
	float length = fabs(D3DXVec3Dot(&Distance, &Cross));
	float bite = length - (r1 + r2);

	return bite;
}

float Collider3D::LenSegOnSeparateAxis(D3DXVECTOR3* Sep,
	D3DXVECTOR3* edge1, D3DXVECTOR3* edge2, D3DXVECTOR3* edge3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは正規化されていること
	float r1 = fabsf(D3DXVec3Dot(Sep, edge1));
	float r2 = fabsf(D3DXVec3Dot(Sep, edge2));
	float r3 = edge3 ? (fabsf(D3DXVec3Dot(Sep, edge3))) : 0;
	return r1 + r2 + r3;
}

void Collider3D::SetMinBiteAndMinBiteAxis(
	float Bite, D3DXVECTOR3 BiteAxis, float& MinBite, D3DXVECTOR3& MinBiteAxis)
{
	if (MinBite > Bite)
	{
		MinBite = Bite;
		MinBiteAxis = BiteAxis;
	}
}

void Collider3D::SetVelocityRef(D3DXVECTOR3* VelocityRef, optional<float> Damp)
{
	m_VelocityRef = VelocityRef;

	if (m_Damp)
	{
		m_Damp = *Damp;
	}
}

void Collider3D::ReflectionVelocityRef(D3DXVECTOR3 Base)
{
	if (m_VelocityRef)
	{
		D3DXVECTOR3 vel = { 0.0f, 0.0f, 0.0f };

		if (Base.x != 0.0f)
		{
			if (m_VelocityRef->x / Base.x < 0.0f)
			{
				vel.x = -m_VelocityRef->x + -m_VelocityRef->x * m_Damp;
			}
		}
		if (Base.y != 0.0f)
		{
			if (m_VelocityRef->y / Base.y < 0.0f)
			{
				vel.y = -m_VelocityRef->y + -m_VelocityRef->y * m_Damp;
			}
		}
		if (Base.z != 0.0f)
		{
			if (m_VelocityRef->z / Base.z < 0.0f)
			{
				vel.z = -m_VelocityRef->z + -m_VelocityRef->z * m_Damp;
			}
		}

		*m_VelocityRef += vel;
	}
}

void Collider3D::DeleteVelocityRef()
{
	m_VelocityRef = NULL;
}

void Collider3D::SetIsTrigger(bool Value)
{
	m_IsTrigger = Value;

	if (!m_IsTrigger)
	{
		// 衝突相手がトリガーで、自身トリガーではない場合は、
		// コールバックは発生しないのでリストから削除する
		auto itr = m_RemainList.begin();
		while (itr != m_RemainList.end())
		{
			if ((*itr)->GetIsTrigger())
			{
				itr = m_RemainList.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
}
