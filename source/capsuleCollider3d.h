/*******************************************************************************
*
*	タイトル：	カプセル型3Dコリジョンコンポーネント	[ capsuleCollider3d.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "collider3d.h"

class CapsuleCollider3D : public Collider3D
{
public:
	enum class DirectionPattern
	{
		X = 0,
		Y,
		Z,
	};

private:
	float m_LocalRadius = 0.0f;
	float m_LocalHeight = 0.0f;
	DirectionPattern m_HeightDirection = DirectionPattern::X;

#ifdef _DEBUG
	static inline int m_QuarterCircleVertexNum = 25;
	static inline int m_HalfCircleVertexNum = m_QuarterCircleVertexNum * 2;
	static inline int m_VertexNum = m_HalfCircleVertexNum * 8 + 5;
	ID3D11Buffer* m_VertexBuffer = NULL;		// 頂点バッファ
	ID3D11VertexShader* m_VertexShader = NULL;	// 頂点シェーダー
	ID3D11PixelShader* m_PixelShader = NULL;	// ピクセルシェーダー
	ID3D11InputLayout* m_VertexLayout = NULL;	// 入力レイアウト
#endif

public:
	CapsuleCollider3D(GameObject* AttachObject) : Collider3D(AttachObject, Collider3D::ColliderId::Capsule) {}

	void Init(D3DXVECTOR3 Offset, float Radius, float Height,
		DirectionPattern HeightDirection,
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
	float GetWorldHeight();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	float GetLocalRadius() { return m_LocalRadius; }
	void SetLocalRadius(float Radius) { m_LocalRadius = Radius; }

	float GetLocalHeight() { return m_LocalHeight; }
	void SetLocalHeight(float Radius) { m_LocalHeight = Radius; }

	DirectionPattern GetDirection() { return m_HeightDirection; }
	void SetDirection(DirectionPattern Direction) { m_HeightDirection = Direction; }
	/////////////////////////////

#ifdef _DEBUG
private:
	void InitDebug() override;
	void UninitDebug() override;
	void DrawDebug() override;
	void CreateVertex(VERTEX_3D* Vertex);
	void CreateVertexAxisX(VERTEX_3D* Vertex, float StraightHalfLen);
	void CreateVertexAxisY(VERTEX_3D* Vertex, float StraightHalfLen);
	void CreateVertexAxisZ(VERTEX_3D* Vertex, float StraightHalfLen);
#endif
};
