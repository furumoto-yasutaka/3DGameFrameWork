/*******************************************************************************
*
*	タイトル：	3Dコリジョン管理用静的クラス	[ collision3dManager.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "collision3dManager.h"
#include "renderer.h"
#include "debugManager.h"

void Collision3DManager::Init(unsigned int Level, D3DXVECTOR3 Min, D3DXVECTOR3 Size)
{
	if (Level > m_TREE_MAX_LEVEL) { return; }

	m_Min = Min;
	m_Size = Size;
	m_Level = Level;

	// 各分割レベルでの空間数を計算
	m_Pow[0] = 1;
	for (int i = 1; i < m_TREE_MAX_LEVEL + 2; i++)
	{
		m_Pow[i] = m_Pow[i - 1] * 8;
	}

	// 空間数を計算
	m_CellNum = (m_Pow[m_Level + 1] - 1) / 7;
	// 空間オブジェクトを生成
	m_TreeCellList = new TreeCell<Collider3D>[m_CellNum];
	// 最小空間の空間サイズを計算
	m_Unit = m_Size / ((float)(1 << m_Level));

#ifdef _DEBUG
	InitDebug();
#endif
}

void Collision3DManager::Uninit()
{
	delete[] m_TreeCellList;

#ifdef _DEBUG
	UninitDebug();
#endif
}

void Collision3DManager::Update()
{
	if (!m_TreeCellList) { return; }

	// コリジョンの所属空間を更新
	UpdateCells();

	// 衝突判定
	list<Collider3D*> stack;
	CheckCollision(0, stack);

	// 衝突コールバックを実行
	CheckCallBack();
}

void Collision3DManager::Draw()
{
#ifdef _DEBUG
	DrawDebug();
#endif
}

/*******************************************************************************
*	コリジョンコンポーネントを空間に登録
*******************************************************************************/
TreeCellData<Collider3D>* Collision3DManager::Regist(Collider3D* Collider)
{
	if (!Collider) { return NULL; }

	// 空間登録用オブジェクト生成・登録
	TreeCellData<Collider3D>* data = new TreeCellData<Collider3D>(Collider);
	m_TreeCellDataList.push_back(data);

	// 空間オブジェクトにコンポーネントを登録する
	DWORD index = GetMortonNumber(Collider->GetMortonMinPos(), Collider->GetMortonMaxPos());
	if (index < m_CellNum)
	{
		m_TreeCellList[index].Push(data);
	}

	return data;
}

/*******************************************************************************
*	コリジョンコンポーネントを空間から削除
*******************************************************************************/
void Collision3DManager::RemoveTreeCellData(TreeCellData<Collider3D>* data)
{
	m_TreeCellDataList.remove(data);

	for (auto itr = m_TreeCellDataList.begin(); itr != m_TreeCellDataList.end(); itr++)
	{
		(*itr)->m_Object->RemoveRemainElement(data->m_Object);
	}
}

/*******************************************************************************
*	空間のパラメータを変更
*******************************************************************************/
void Collision3DManager::ResetSpace(unsigned int Level, D3DXVECTOR3 Min, D3DXVECTOR3 Size)
{
	// 空間オブジェクトが一度消えるため一旦空間から離脱させる
	for (auto itr = m_TreeCellDataList.begin(); itr != m_TreeCellDataList.end(); itr++)
	{
		(*itr)->Remove();
	}

	m_Level = Level;
	m_Min = Min;
	m_Size = Size;

	// 空間数を計算
	m_CellNum = (m_Pow[m_Level + 1] - 1) / 7;
	// 空間オブジェクトを生成
	delete[] m_TreeCellList;
	m_TreeCellList = new TreeCell<Collider3D>[m_CellNum];
	// 最小空間の空間サイズを計算
	m_Unit = m_Size / ((float)(1 << m_Level));

	// 再登録処理
	for (auto itr = m_TreeCellDataList.begin(); itr != m_TreeCellDataList.end(); itr++)
	{
		DWORD index = GetMortonNumber((*itr)->m_Object->GetMortonMinPos(), (*itr)->m_Object->GetMortonMaxPos());
		if (index < m_CellNum)
		{
			m_TreeCellList[index].Push((*itr));
		}
	}

#ifdef _DEBUG
	UninitDebug();
	InitDebug();
#endif
}

/*******************************************************************************
*	コリジョンコンポーネントの所属空間の更新
*******************************************************************************/
void Collision3DManager::UpdateCells()
{
	for (auto itr = m_TreeCellDataList.begin(); itr != m_TreeCellDataList.end(); itr++)
	{
		// 一旦所属空間から離脱
		(*itr)->Remove();

		// 登録処理
		DWORD index = GetMortonNumber((*itr)->m_Object->GetMortonMinPos(), (*itr)->m_Object->GetMortonMaxPos());
		if (index < m_CellNum)
		{
			m_TreeCellList[index].Push((*itr));
		}
	}
}

/*******************************************************************************
*	衝突判定(再帰処理)
*******************************************************************************/
void Collision3DManager::CheckCollision(DWORD Index, list<Collider3D*>& Stack)
{
	TreeCellData<Collider3D>* baseData = m_TreeCellList[Index].GetDataList();
	TreeCellData<Collider3D>* pertnerData;
	list<Collider3D*> objList;
	int objCount = 0;

	// 空間内のオブジェクトと衝突判定をする
	while (baseData)
	{
		if (baseData->m_Object->GetActive())
		{		
			// 同じ空間のオブジェクトと判定
			pertnerData = baseData->m_Next;
			while (pertnerData)
			{
				if (pertnerData->m_Object->GetActive())
				{
					baseData->m_Object->Collision(pertnerData->m_Object);
				}
				pertnerData = pertnerData->m_Next;
			}

			// 親にあたる空間のオブジェクトを格納したスタックと判定
			for (auto pertnerDataItr = Stack.begin(); pertnerDataItr != Stack.end(); pertnerDataItr++)
			{
				if (!(*pertnerDataItr)->GetActive()) { continue; }

				baseData->m_Object->Collision((*pertnerDataItr));
			}
		}

		// スタック登録用のリストに追加
		objList.push_back(baseData->m_Object);
		// 次のデータへ進める
		baseData = baseData->m_Next;
		objCount++;
	}
	// スタックに連結
	Stack.splice(Stack.end(), objList);

	// 子空間の衝突判定を進める
	DWORD ChildIndex = Index * 8 + 1;
	if (ChildIndex < m_CellNum)
	{
		for (int i = 0; i < 8; i++, ChildIndex++)
		{
			CheckCollision(ChildIndex, Stack);
		}
	}

	// スタックからこの空間のオブジェクトを外す
	auto itr = Stack.rbegin();
	for (int i = 0; i < objCount - 1; i++)
	{
		itr++;
	}
	Stack.erase(itr.base(), Stack.end());
}

/*******************************************************************************
*	衝突コールバック処理
*******************************************************************************/
void Collision3DManager::CheckCallBack()
{
	for (TreeCellData<Collider3D>* c : m_TreeCellDataList)
	{
		c->m_Object->CheckCallBack();
	}
}

/*******************************************************************************
*	所属空間をモートン番号で求める
*******************************************************************************/
DWORD Collision3DManager::GetMortonNumber(D3DXVECTOR3 Min, D3DXVECTOR3 Max)
{
	// 最小レベルにおける所属空間を計算
	DWORD minPoint = GetCellIndex(Min);
	DWORD maxPoint = GetCellIndex(Max);

	DWORD sub = maxPoint ^ minPoint;
	int i = 0;
	int shift = 0;
	int level = 0;
	while (sub != 0)
	{
		if ((sub & 0x7) != 0)
		{
			level = i + 1;
			shift = level * 3;
		}

		sub >>= 3;
		i++;
	}
	int morton = maxPoint >> shift;

	return morton;


	//DWORD sub = maxPoint ^ minPoint;
	//int level = 1;
	//int i = 0;
	//for (; i < m_Level; i++)
	//{
	//	DWORD check = (sub >> (i * 3)) & 0x7;
	//	if (check != 0)
	//	{
	//		level = i + 1;
	//	}
	//}
	//DWORD spaceNum = maxPoint >> (level * 3);
	//DWORD add = (m_Pow[m_Level - level] - 1) / 7;
	//spaceNum += add;

	//if (spaceNum > m_CellNum)
	//{
	//	return 0xffffffff;
	//}

	//return spaceNum;

	//DWORD sub = maxPoint ^ minPoint;
	//int level = 0;
	//int i = 0;
	//while (sub != 0)
	//{
	//	DWORD check = sub & 0x7;
	//	if (check != 0) { level = i + 1; }

	//	sub >>= 3;
	//	i++;
	//}
	//DWORD cellIndex = maxPoint >> (level * 3);

	//return cellIndex;
}

/*******************************************************************************
*	座標→線形8分木要素番号変換
*******************************************************************************/
DWORD Collision3DManager::GetCellIndex(D3DXVECTOR3 Pos)
{
	BYTE x, y, z;

	Pos -= m_Min;
	x = (BYTE)(Pos.x / m_Unit.x);
	y = (BYTE)(Pos.y / m_Unit.y);
	z = (BYTE)(Pos.z / m_Unit.z);

	return BitSeparate(x) | BitSeparate(y) << 1 | BitSeparate(z) << 2;
}

/*******************************************************************************
*	座標→線形8分木要素番号変換
*******************************************************************************/
DWORD Collision3DManager::BitSeparate(BYTE n)
{
	DWORD s = n;
	s = (s | s << 8) & 0x0000f00f;
	s = (s | s << 4) & 0x000c30c3;
	s = (s | s << 2) & 0x00249249;
	return s;
}

/*******************************************************************************
*	デバッグ用関数
*******************************************************************************/
#ifdef _DEBUG
void Collision3DManager::InitDebug()
{
	//-------------------
	// バッファ設定
	//-------------------
	m_VertexNum = (m_Level + 2) * (m_Level + 2) * 3 * 2;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * m_VertexNum;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// 軸に平行な線の数 * 3軸 * 2頂点
	VERTEX_3D* vertex = new VERTEX_3D[m_VertexNum];
	D3D11_SUBRESOURCE_DATA sd;
	CreateVertex(vertex);
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	// バッファ生成
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// シェーダー設定
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "debugLineVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "debugLinePS.cso");
}

void Collision3DManager::UninitDebug()
{
	m_VertexBuffer->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void Collision3DManager::DrawDebug()
{
	printf("%d                        \n", m_CollisionCount);
	m_CollisionCount = 0;

	if (!DebugManager::m_IsSpaceDivisionFrame) return;

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	Renderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(m_VertexNum, 0);
}

void Collision3DManager::CreateVertex(VERTEX_3D* Vertex)
{
	int i, j, index;
	index = 0;
	int column = (m_Level + 1);
	float rate = 1.0f / column;

	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR d = D3DXCOLOR(1.0f, 0.3f, 1.0f, 1.0f);
	D3DXVECTOR2 c = D3DXVECTOR2(0.0f, 0.0f);

	// X軸
	for (i = 0; i < column + 1; i++)
	{
		for (j = 0; j < column + 1; j++)
		{
			Vertex[index].Position = m_Min + D3DXVECTOR3(0.0f, i * rate * m_Size.y, j * rate * m_Size.z);
			Vertex[index].Normal = n;
			Vertex[index].Diffuse = d;
			Vertex[index].TexCoord = c;

			index++;

			Vertex[index].Position = m_Min + D3DXVECTOR3(m_Size.x, i * rate * m_Size.y, j * rate * m_Size.z);
			Vertex[index].Normal = n;
			Vertex[index].Diffuse = d;
			Vertex[index].TexCoord = c;

			index++;
		}
	}

	// Y軸
	for (i = 0; i < column + 1; i++)
	{
		for (j = 0; j < column + 1; j++)
		{
			Vertex[index].Position = m_Min + D3DXVECTOR3(i * rate * m_Size.x, 0.0f, j * rate * m_Size.z);
			Vertex[index].Normal = n;
			Vertex[index].Diffuse = d;
			Vertex[index].TexCoord = c;

			index++;

			Vertex[index].Position = m_Min + D3DXVECTOR3(i * rate * m_Size.x, m_Size.y, j * rate * m_Size.z);
			Vertex[index].Normal = n;
			Vertex[index].Diffuse = d;
			Vertex[index].TexCoord = c;

			index++;
		}
	}

	// Z軸
	for (i = 0; i < column + 1; i++)
	{
		for (j = 0; j < column + 1; j++)
		{
			Vertex[index].Position = m_Min + D3DXVECTOR3(i * rate * m_Size.x, j * rate * m_Size.y, 0.0f);
			Vertex[index].Normal = n;
			Vertex[index].Diffuse = d;
			Vertex[index].TexCoord = c;

			index++;

			Vertex[index].Position = m_Min + D3DXVECTOR3(i * rate * m_Size.x, j * rate * m_Size.y, m_Size.z);
			Vertex[index].Normal = n;
			Vertex[index].Diffuse = d;
			Vertex[index].TexCoord = c;

			index++;
		}
	}
}
#endif
