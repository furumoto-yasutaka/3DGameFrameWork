/*******************************************************************************
*
*	�^�C�g���F	���^3D�R���W�����R���|�[�l���g	[ sphereCollider3d.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "collider3d.h"

class SphereCollider3D : public Collider3D
{
private:
	float m_LocalRadius = 0.0f;

#ifdef _DEBUG
	static inline int m_QuarterCircleVertexNum = 25;
	static inline int m_CircleVertexNum = m_QuarterCircleVertexNum * 4;
	static inline int m_VertexNum = m_CircleVertexNum * 3 + 1;
	ID3D11Buffer* m_VertexBuffer = NULL;		// ���_�o�b�t�@
	ID3D11VertexShader* m_VertexShader = NULL;	// ���_�V�F�[�_�[
	ID3D11PixelShader* m_PixelShader = NULL;	// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout* m_VertexLayout = NULL;	// ���̓��C�A�E�g
#endif

public:
	SphereCollider3D(GameObject* AttachObject) : Collider3D(AttachObject, Collider3D::ColliderId::Sphere) {}

	void Init(D3DXVECTOR3 Offset, float Radius,
		bool IsTrigger = false, bool IsStatic = false);
	void Uninit() override;
	void Update() override {}
	void Draw() override;

	void CollisionAABB(AABBCollider3D* Collider) override;
	void CollisionOBB(OBBCollider3D* Collider) override;
	void CollisionSphere(SphereCollider3D* Collider) override;
	void CollisionCapsule(CapsuleCollider3D* Collider) override;

	D3DXVECTOR3 GetMortonMinPos() override;
	D3DXVECTOR3 GetMortonMaxPos() override;

	float GetWorldRadius();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	float GetLocalRadius() { return m_LocalRadius; }
	void SetRadius(float Radius) { m_LocalRadius = Radius; }
	/////////////////////////////

#ifdef _DEBUG
private:
	void InitDebug() override;
	void UninitDebug() override;
	void DrawDebug() override;
	void CreateVertex(VERTEX_3D* Vertex);
#endif
};
