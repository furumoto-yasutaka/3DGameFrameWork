/*******************************************************************************
*
*	タイトル：	3Dコリジョン基底クラス	[ collider3d.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "physicsComponent.h"
#include "callbackListner.h"

#include <list>
#include <optional>

template<class T>
class TreeCellData;
class AABBCollider3D;
class OBBCollider3D;
class SphereCollider3D;
class CapsuleCollider3D;
struct VERTEX_3D;

class Collider3D : public PhysicsComponent
{
public:
	enum class ColliderId
	{
		AABB,
		OBB,
		Sphere,
		Capsule,
	};

protected:
	TreeCellData<Collider3D>* m_ThisCellData = NULL;
	ColliderId m_Id;
	D3DXVECTOR3 m_Offset;
	bool m_IsContact = false;
	bool m_IsPrevContact = false;
	bool m_IsTrigger = false;
	bool m_IsStatic = false;
	list<Collider3D*> m_ContactList;	// 現在衝突しているオブジェクトのリスト
	list<Collider3D*> m_RemainList;		// 前フレームに衝突しているオブジェクトのリスト

	D3DXVECTOR3* m_VelocityRef = NULL;	// 衝突を速度に反映させる為の参照
	float m_Damp = 0.0f;				// 衝突時の反射係数

	CallBackArgumentBase<Collider3D>* m_OnContactEnter = NULL;	// 接触開始フレームのコールバック関数
	CallBackArgumentBase<Collider3D>* m_OnContactStay = NULL;	// 接触中のコールバック関数
	CallBackArgumentBase<Collider3D>* m_OnContactExit = NULL;	// 接触終了フレームのコールバック関数

public:
	Collider3D(GameObject* AttachObject, ColliderId Id)
		: PhysicsComponent(AttachObject), m_Id(Id) {}

protected:
	void Init(D3DXVECTOR3 Offset, bool IsTrigger, bool IsStatic);
public:
	virtual void Uninit();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void Collision(Collider3D* Collider);
	virtual void CollisionAABB(AABBCollider3D* Collider) = 0;
	virtual void CollisionOBB(OBBCollider3D* Collider) = 0;
	virtual void CollisionSphere(SphereCollider3D* Collider) = 0;
	virtual void CollisionCapsule(CapsuleCollider3D* Collider) = 0;

	D3DXVECTOR3 GetColliderWorldPos();
	virtual D3DXVECTOR3 GetMortonMinPos() = 0;
	virtual D3DXVECTOR3 GetMortonMaxPos() = 0;

	void CheckCallBack();

	// 接触開始フレームのコールバック関数を登録
	template<class T>
	void SetOnContactEnter(T* Origin, void(T::* Function)(Collider3D*))
	{
		m_OnContactEnter = new CallBackArgumentListner<T, Collider3D>(Origin, Function);
	}

	// 接触中のコールバック関数を登録
	template<class T>
	void SetOnContactStay(T* Origin, void(T::* Function)(Collider3D*))
	{
		m_OnContactStay = new CallBackArgumentListner<T, Collider3D>(Origin, Function);
	}

	// 接触終了フレームのコールバック関数を登録
	template<class T>
	void SetOnContactExit(T* Origin, void(T::* Function)(Collider3D*))
	{
		m_OnContactExit = new CallBackArgumentListner<T, Collider3D>(Origin, Function);
	}

	void CallOnContactEnter(Collider3D* Collider);
	void CallOnContactStay(Collider3D* Collider);
	void CallOnContactExit(Collider3D* Collider);

	void AddContactList(Collider3D* Collider);
	void RemoveRemainElement(Collider3D* Collider);

	float CalcDirectionVectorSeparateAxisLength(
		D3DXVECTOR3 A_DirVec, D3DXVECTOR3 A_DirVecNormal,
		D3DXVECTOR3 B_DirVecRight, D3DXVECTOR3 B_DirVecUp, D3DXVECTOR3 B_DirVecForward,
		D3DXVECTOR3 Distance);
	float CalcCrossSeparateAxisLength(D3DXVECTOR3 Cross,
		D3DXVECTOR3 A_DirVec1, D3DXVECTOR3 A_DirVec2,
		D3DXVECTOR3 B_DirVec1, D3DXVECTOR3 B_DirVec2,
		D3DXVECTOR3 Distance);
	float LenSegOnSeparateAxis(D3DXVECTOR3* Sep,
		D3DXVECTOR3* edge1, D3DXVECTOR3* edge2, D3DXVECTOR3* edge3 = NULL);
	void SetMinBiteAndMinBiteAxis(
		float Bite, D3DXVECTOR3 BiteAxis, float& MinBite, D3DXVECTOR3& MinBiteAxis);

	void SetVelocityRef(D3DXVECTOR3* VelocityRef, optional<float> Damp);
	void ReflectionVelocityRef(D3DXVECTOR3 Base);
	void DeleteVelocityRef();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	ColliderId GetId() { return m_Id; }
	D3DXVECTOR3 GetOffset() { return m_Offset; }
	bool GetIsTrigger() { return m_IsTrigger; }
	void SetIsTrigger(bool Value);
	bool GetIsStatic() { return m_IsStatic; }
	void SetIsStatic(bool Value) { m_IsStatic = Value; }
	list<Collider3D*> GetContactList() { return m_RemainList; }
	D3DXVECTOR3* GetVelocityRef() { return m_VelocityRef; }
	/////////////////////////////

#ifdef _DEBUG
protected:
	virtual void InitDebug() = 0;
	virtual void UninitDebug() = 0;
	virtual void DrawDebug() = 0;
#endif
};
