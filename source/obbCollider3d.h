/*******************************************************************************
*
*	タイトル：	有向境界3Dコリジョンコンポーネント	[ obbCollider3d.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "collider3d.h"

class OBBCollider3D : public Collider3D
{
private:
	D3DXVECTOR3	m_LocalRadius;

#ifdef _DEBUG
	ID3D11Buffer* m_VertexBuffer[4] = { NULL, NULL, NULL, NULL };	// 頂点バッファ
	ID3D11VertexShader* m_VertexShader = NULL;	// 頂点シェーダー
	ID3D11PixelShader* m_PixelShader = NULL;	// ピクセルシェーダー
	ID3D11InputLayout* m_VertexLayout = NULL;	// 入力レイアウト
#endif

public:
	OBBCollider3D(GameObject* AttachObject) : Collider3D(AttachObject, Collider3D::ColliderId::OBB) {}

	void Init(D3DXVECTOR3 Offset, D3DXVECTOR3 Radius,
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

	D3DXVECTOR3 GetWorldRadius();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	D3DXVECTOR3 GetRadius() { return m_LocalRadius; }
	void SetRadius(D3DXVECTOR3 Radius) { m_LocalRadius = Radius; }
	/////////////////////////////

#ifdef _DEBUG
private:
	void InitDebug() override;
	void UninitDebug() override;
	void DrawDebug() override;
	void CreateVertex(VERTEX_3D* Vertex, int Index, D3DXVECTOR3 vertexPos[2][4]);
#endif
};
