/*******************************************************************************
*
*	タイトル：	有向境界3Dコリジョンコンポーネント	[ obbCollider3d.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "obbCollider3d.h"
#include "gameObject.h"
#include "aabbCollider3d.h"
#include "sphereCollider3d.h"
#include "capsuleCollider3d.h"

#ifdef _DEBUG
#include "debugManager.h"
#endif

void OBBCollider3D::Init(D3DXVECTOR3 Offset, D3DXVECTOR3 Radius,
	bool IsTrigger, bool IsStatic)
{
	Collider3D::Init(Offset, IsTrigger, IsStatic);

	m_LocalRadius = Radius;

#ifdef _DEBUG
	InitDebug();
#endif
}

void OBBCollider3D::Uninit()
{
	Collider3D::Uninit();

#ifdef _DEBUG
	UninitDebug();
#endif
}

void OBBCollider3D::Draw()
{
#ifdef _DEBUG
	DrawDebug();
#endif
}

void OBBCollider3D::CollisionAABB(AABBCollider3D* Collider)
{
	D3DXVECTOR3 thisRadius = GetWorldRadius();
	D3DXVECTOR3 targetRadius = Collider->GetWorldRadius();
	D3DXVECTOR3 thisCenter = GetColliderWorldPos();
	D3DXVECTOR3 targetCenter = Collider->GetColliderWorldPos();
	D3DXVECTOR3 distance = targetCenter - thisCenter;

	// 各方向ベクトルの確保
	// 末尾が1：右ベクトル
	// 末尾が2：上ベクトル
	// 末尾が3：前ベクトル
	D3DXVECTOR3 nThis1 = m_AttachObject->GetRight(),
		This1 = nThis1 * thisRadius.x,
		nThis2 = m_AttachObject->GetUp(),
		This2 = nThis2 * thisRadius.y,
		nThis3 = m_AttachObject->GetForward(),
		This3 = nThis3 * thisRadius.z;
	D3DXVECTOR3 nTarget1 = Collider->GetAttachObject()->GetRight(),
		Target1 = nTarget1 * targetRadius.x,
		nTarget2 = Collider->GetAttachObject()->GetUp(),
		Target2 = nTarget2 * targetRadius.y,
		nTarget3 = Collider->GetAttachObject()->GetForward(),
		Target3 = nTarget3 * targetRadius.z;

	float minBite;
	D3DXVECTOR3 minBiteAxis;

	// 分離軸：This1
	float bite = CalcDirectionVectorSeparateAxisLength(This1, nThis1, Target1, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	minBite = bite;
	minBiteAxis = nThis1;

	// 分離軸：This2
	bite = CalcDirectionVectorSeparateAxisLength(This2, nThis2, Target1, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nThis2, minBite, minBiteAxis);

	// 分離軸：This3
	bite = CalcDirectionVectorSeparateAxisLength(This3, nThis3, Target1, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nThis3, minBite, minBiteAxis);

	// 分離軸：Target1
	bite = CalcDirectionVectorSeparateAxisLength(Target1, nTarget1, This1, This2, This3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nTarget1, minBite, minBiteAxis);

	// 分離軸：Target2
	bite = CalcDirectionVectorSeparateAxisLength(Target2, nTarget2, This1, This2, This3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nTarget2, minBite, minBiteAxis);

	// 分離軸：Target3
	bite = CalcDirectionVectorSeparateAxisLength(Target3, nTarget3, This1, This2, This3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nTarget3, minBite, minBiteAxis);

	// 分離軸：This1とTarget1の外積
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &nThis1, &nTarget1);
	bite = CalcCrossSeparateAxisLength(cross, This2, This3, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This1とTarget2の外積
	D3DXVec3Cross(&cross, &nThis1, &nTarget2);
	bite = CalcCrossSeparateAxisLength(cross, This2, This3, Target1, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This1とTarget3の外積
	D3DXVec3Cross(&cross, &nThis1, &nTarget3);
	bite = CalcCrossSeparateAxisLength(cross, This2, This3, Target1, Target2, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This2とTarget1の外積
	D3DXVec3Cross(&cross, &nThis2, &nTarget1);
	bite = CalcCrossSeparateAxisLength(cross, This1, This3, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This2とTarget2の外積
	D3DXVec3Cross(&cross, &nThis2, &nTarget2);
	bite = CalcCrossSeparateAxisLength(cross, This1, This3, Target1, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This2とTarget3の外積
	D3DXVec3Cross(&cross, &nThis2, &nTarget3);
	bite = CalcCrossSeparateAxisLength(cross, This1, This3, Target1, Target2, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This3とTarget1の外積
	D3DXVec3Cross(&cross, &nThis3, &nTarget1);
	bite = CalcCrossSeparateAxisLength(cross, This1, This2, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This3とTarget2の外積
	D3DXVec3Cross(&cross, &nThis3, &nTarget2);
	bite = CalcCrossSeparateAxisLength(cross, This1, This2, Target1, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This3とTarget3の外積
	D3DXVec3Cross(&cross, &nThis3, &nTarget3);
	bite = CalcCrossSeparateAxisLength(cross, This1, This2, Target1, Target2, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 衝突が確定
	AddContactList(Collider);
	Collider->AddContactList(this);

	//// お互いがトリガーではない場合押し出し処理を行う
	//if (!m_IsTrigger && !Collider->GetIsTrigger())
	//{
	//	// 反射処理
	//	ReflectionVelocityRef(minBiteAxis);
	//	Collider->ReflectionVelocityRef(-minBiteAxis);

	//	// 押し出しを反映
	//	D3DXVECTOR3 adjust = minBiteAxis * minBite;
	//	if (!m_IsStatic && !Collider->GetIsStatic())
	//	{
	//		m_AttachObject->GetRoot()->m_LocalPosition -= adjust * 0.5f;
	//		Collider->GetAttachObject()->GetRoot()->m_LocalPosition += adjust * 0.5f;
	//	}
	//	else if (!m_IsStatic)
	//	{
	//		m_AttachObject->GetRoot()->m_LocalPosition -= adjust;
	//	}
	//	else
	//	{
	//		Collider->GetAttachObject()->GetRoot()->m_LocalPosition += adjust;
	//	}
	//}
}

void OBBCollider3D::CollisionOBB(OBBCollider3D* Collider)
{
	D3DXVECTOR3 thisRadius = GetWorldRadius();
	D3DXVECTOR3 targetRadius = Collider->GetWorldRadius();
	D3DXVECTOR3 thisCenter = GetColliderWorldPos();
	D3DXVECTOR3 targetCenter = Collider->GetColliderWorldPos();
	D3DXVECTOR3 distance = targetCenter - thisCenter;

	// 各方向ベクトルの確保
	// 末尾が1：右ベクトル
	// 末尾が2：上ベクトル
	// 末尾が3：前ベクトル
	D3DXVECTOR3 nThis1 = m_AttachObject->GetRight(),
		This1 = nThis1 * thisRadius.x,
		nThis2 = m_AttachObject->GetUp(),
		This2 = nThis2 * thisRadius.y,
		nThis3 = m_AttachObject->GetForward(),
		This3 = nThis3 * thisRadius.z;
	D3DXVECTOR3 nTarget1 = Collider->GetAttachObject()->GetRight(),
		Target1 = nTarget1 * targetRadius.x,
		nTarget2 = Collider->GetAttachObject()->GetUp(),
		Target2 = nTarget2 * targetRadius.y,
		nTarget3 = Collider->GetAttachObject()->GetForward(),
		Target3 = nTarget3 * targetRadius.z;

	float minBite;
	D3DXVECTOR3 minBiteAxis;

	// 分離軸：This1
	float bite = CalcDirectionVectorSeparateAxisLength(This1, nThis1, Target1, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	minBite = bite;
	minBiteAxis = nThis1;

	// 分離軸：This2
	bite = CalcDirectionVectorSeparateAxisLength(This2, nThis2, Target1, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nThis2, minBite, minBiteAxis);

	// 分離軸：This3
	bite = CalcDirectionVectorSeparateAxisLength(This3, nThis3, Target1, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nThis3, minBite, minBiteAxis);

	// 分離軸：Target1
	bite = CalcDirectionVectorSeparateAxisLength(Target1, nTarget1, This1, This2, This3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nTarget1, minBite, minBiteAxis);

	// 分離軸：Target2
	bite = CalcDirectionVectorSeparateAxisLength(Target2, nTarget2, This1, This2, This3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nTarget2, minBite, minBiteAxis);

	// 分離軸：Target3
	bite = CalcDirectionVectorSeparateAxisLength(Target3, nTarget3, This1, This2, This3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, nTarget3, minBite, minBiteAxis);

	// 分離軸：This1とTarget1の外積
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &nThis1, &nTarget1);
	bite = CalcCrossSeparateAxisLength(cross, This2, This3, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This1とTarget2の外積
	D3DXVec3Cross(&cross, &nThis1, &nTarget2);
	bite = CalcCrossSeparateAxisLength(cross, This2, This3, Target1, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This1とTarget3の外積
	D3DXVec3Cross(&cross, &nThis1, &nTarget3);
	bite = CalcCrossSeparateAxisLength(cross, This2, This3, Target1, Target2, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This2とTarget1の外積
	D3DXVec3Cross(&cross, &nThis2, &nTarget1);
	bite = CalcCrossSeparateAxisLength(cross, This1, This3, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This2とTarget2の外積
	D3DXVec3Cross(&cross, &nThis2, &nTarget2);
	bite = CalcCrossSeparateAxisLength(cross, This1, This3, Target1, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This2とTarget3の外積
	D3DXVec3Cross(&cross, &nThis2, &nTarget3);
	bite = CalcCrossSeparateAxisLength(cross, This1, This3, Target1, Target2, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This3とTarget1の外積
	D3DXVec3Cross(&cross, &nThis3, &nTarget1);
	bite = CalcCrossSeparateAxisLength(cross, This1, This2, Target2, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This3とTarget2の外積
	D3DXVec3Cross(&cross, &nThis3, &nTarget2);
	bite = CalcCrossSeparateAxisLength(cross, This1, This2, Target1, Target3, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 分離軸：This3とTarget3の外積
	D3DXVec3Cross(&cross, &nThis3, &nTarget3);
	bite = CalcCrossSeparateAxisLength(cross, This1, This2, Target1, Target2, distance);
	if (bite > 0.0f) { return; }
	SetMinBiteAndMinBiteAxis(bite, cross, minBite, minBiteAxis);

	// 衝突が確定
	AddContactList(Collider);
	Collider->AddContactList(this);

	//// お互いがトリガーではない場合押し出し処理を行う
	//if (!m_IsTrigger && !Collider->GetIsTrigger())
	//{
	//	// 反射処理
	//	ReflectionVelocityRef(minBiteAxis);
	//	Collider->ReflectionVelocityRef(-minBiteAxis);

	//	// 押し出しを反映
	//	D3DXVECTOR3 adjust = minBiteAxis * minBite;
	//	if (!m_IsStatic && !Collider->GetIsStatic())
	//	{
	//		m_AttachObject->GetRoot()->m_LocalPosition -= adjust * 0.5f;
	//		Collider->GetAttachObject()->GetRoot()->m_LocalPosition += adjust * 0.5f;
	//	}
	//	else if (!m_IsStatic)
	//	{
	//		m_AttachObject->GetRoot()->m_LocalPosition -= adjust;
	//	}
	//	else
	//	{
	//		Collider->GetAttachObject()->GetRoot()->m_LocalPosition += adjust;
	//	}
	//}
}

void OBBCollider3D::CollisionSphere(SphereCollider3D* Collider)
{

}

void OBBCollider3D::CollisionCapsule(CapsuleCollider3D* Collider)
{

}

D3DXVECTOR3 OBBCollider3D::GetMortonMinPos()
{
	return GetColliderWorldPos() - GetWorldRadius();
}

D3DXVECTOR3 OBBCollider3D::GetMortonMaxPos()
{
	return GetColliderWorldPos() + GetWorldRadius();
}

D3DXVECTOR3 OBBCollider3D::GetWorldRadius()
{
	D3DXVECTOR3 scale = m_AttachObject->GetWorldScale();
	D3DXVECTOR3 radius = {
		m_LocalRadius.x * scale.x,
		m_LocalRadius.y * scale.y,
		m_LocalRadius.z * scale.z,
	};

	return radius;
}

/*******************************************************************************
*	デバッグ用関数
*******************************************************************************/
#ifdef _DEBUG
void OBBCollider3D::InitDebug()
{
	//-------------------
	// バッファ設定
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3DXVECTOR3 radius = GetWorldRadius();
	D3DXVECTOR3 boxMinPoint = m_Offset - radius;
	D3DXVECTOR3 boxMaxPoint = m_Offset + radius;

	D3DXVECTOR3 vertexPos[2][4];
	// 上段
	vertexPos[0][0] = D3DXVECTOR3(boxMinPoint.x, boxMaxPoint.y, boxMinPoint.z);
	vertexPos[0][1] = D3DXVECTOR3(boxMaxPoint.x, boxMaxPoint.y, boxMinPoint.z);
	vertexPos[0][2] = D3DXVECTOR3(boxMaxPoint.x, boxMaxPoint.y, boxMaxPoint.z);
	vertexPos[0][3] = D3DXVECTOR3(boxMinPoint.x, boxMaxPoint.y, boxMaxPoint.z);
	// 下段
	vertexPos[1][0] = D3DXVECTOR3(boxMinPoint.x, boxMinPoint.y, boxMinPoint.z);
	vertexPos[1][1] = D3DXVECTOR3(boxMaxPoint.x, boxMinPoint.y, boxMinPoint.z);
	vertexPos[1][2] = D3DXVECTOR3(boxMaxPoint.x, boxMinPoint.y, boxMaxPoint.z);
	vertexPos[1][3] = D3DXVECTOR3(boxMinPoint.x, boxMinPoint.y, boxMaxPoint.z);

	VERTEX_3D vertex[4];
	D3D11_SUBRESOURCE_DATA sd;
	for (int i = 0; i < 4; i++)
	{
		CreateVertex(vertex, i, vertexPos);

		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		// バッファ生成
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[i]);
	}

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "debugLineVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "debugLinePS.cso");
}

void OBBCollider3D::UninitDebug()
{
	for (int i = 0; i < 4; i++)
	{
		m_VertexBuffer[i]->Release();
	}
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void OBBCollider3D::DrawDebug()
{
	if (!DebugManager::m_IsCollisionFrame) return;

	D3DXVECTOR3 radius = GetWorldRadius();
	D3DXVECTOR3 boxMinPoint = m_Offset - radius;
	D3DXVECTOR3 boxMaxPoint = m_Offset + radius;

	D3DXVECTOR3 vertexPos[2][4];
	// 上段
	vertexPos[0][0] = D3DXVECTOR3(boxMinPoint.x, boxMaxPoint.y, boxMinPoint.z);
	vertexPos[0][1] = D3DXVECTOR3(boxMaxPoint.x, boxMaxPoint.y, boxMinPoint.z);
	vertexPos[0][2] = D3DXVECTOR3(boxMaxPoint.x, boxMaxPoint.y, boxMaxPoint.z);
	vertexPos[0][3] = D3DXVECTOR3(boxMinPoint.x, boxMaxPoint.y, boxMaxPoint.z);
	// 下段
	vertexPos[1][0] = D3DXVECTOR3(boxMinPoint.x, boxMinPoint.y, boxMinPoint.z);
	vertexPos[1][1] = D3DXVECTOR3(boxMaxPoint.x, boxMinPoint.y, boxMinPoint.z);
	vertexPos[1][2] = D3DXVECTOR3(boxMaxPoint.x, boxMinPoint.y, boxMaxPoint.z);
	vertexPos[1][3] = D3DXVECTOR3(boxMinPoint.x, boxMinPoint.y, boxMaxPoint.z);

	for (int i = 0; i < 4; i++)
	{
		// 頂点情報書き換え
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer[i], 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
		CreateVertex(vertex, i, vertexPos);
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer[i], 0);

		// 入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		// シェーダ設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		// ワールドマトリクス設定
		D3DXMATRIX m = m_AttachObject->GetWorldMatrix();
		Renderer::SetWorldMatrix(&m);

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer[i], &stride, &offset);

		// マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		Renderer::SetMaterial(material);

		// プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		// ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

void OBBCollider3D::CreateVertex(VERTEX_3D* Vertex, int Index, D3DXVECTOR3 vertexPos[2][4])
{
	int next = (Index + 1) % 4;

	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR d = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	D3DXVECTOR2 c = D3DXVECTOR2(0.0f, 0.0f);

	Vertex[0].Position = vertexPos[0][Index];
	Vertex[0].Normal = n;
	Vertex[0].Diffuse = d;
	Vertex[0].TexCoord = c;

	Vertex[1].Position = vertexPos[0][next];
	Vertex[1].Normal = n;
	Vertex[1].Diffuse = d;
	Vertex[1].TexCoord = c;

	Vertex[2].Position = vertexPos[1][next];
	Vertex[2].Normal = n;
	Vertex[2].Diffuse = d;
	Vertex[2].TexCoord = c;

	Vertex[3].Position = vertexPos[1][Index];
	Vertex[3].Normal = n;
	Vertex[3].Diffuse = d;
	Vertex[3].TexCoord = c;
}
#endif
