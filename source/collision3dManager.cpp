/*******************************************************************************
*
*	�^�C�g���F	3D�R���W�����Ǘ��p�ÓI�N���X	[ collision3dManager.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

	// �e�������x���ł̋�Ԑ����v�Z
	m_Pow[0] = 1;
	for (int i = 1; i < m_TREE_MAX_LEVEL + 2; i++)
	{
		m_Pow[i] = m_Pow[i - 1] * 8;
	}

	// ��Ԑ����v�Z
	m_CellNum = (m_Pow[m_Level + 1] - 1) / 7;
	// ��ԃI�u�W�F�N�g�𐶐�
	m_TreeCellList = new TreeCell<Collider3D>[m_CellNum];
	// �ŏ���Ԃ̋�ԃT�C�Y���v�Z
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

	// �R���W�����̏�����Ԃ��X�V
	UpdateCells();

	// �Փ˔���
	list<Collider3D*> stack;
	CheckCollision(0, stack);

	// �Փ˃R�[���o�b�N�����s
	CheckCallBack();
}

void Collision3DManager::Draw()
{
#ifdef _DEBUG
	DrawDebug();
#endif
}

/*******************************************************************************
*	�R���W�����R���|�[�l���g����Ԃɓo�^
*******************************************************************************/
TreeCellData<Collider3D>* Collision3DManager::Regist(Collider3D* Collider)
{
	if (!Collider) { return NULL; }

	// ��ԓo�^�p�I�u�W�F�N�g�����E�o�^
	TreeCellData<Collider3D>* data = new TreeCellData<Collider3D>(Collider);
	m_TreeCellDataList.push_back(data);

	// ��ԃI�u�W�F�N�g�ɃR���|�[�l���g��o�^����
	DWORD index = GetMortonNumber(Collider->GetMortonMinPos(), Collider->GetMortonMaxPos());
	if (index < m_CellNum)
	{
		m_TreeCellList[index].Push(data);
	}

	return data;
}

/*******************************************************************************
*	�R���W�����R���|�[�l���g����Ԃ���폜
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
*	��Ԃ̃p�����[�^��ύX
*******************************************************************************/
void Collision3DManager::ResetSpace(unsigned int Level, D3DXVECTOR3 Min, D3DXVECTOR3 Size)
{
	// ��ԃI�u�W�F�N�g����x�����邽�߈�U��Ԃ��痣�E������
	for (auto itr = m_TreeCellDataList.begin(); itr != m_TreeCellDataList.end(); itr++)
	{
		(*itr)->Remove();
	}

	m_Level = Level;
	m_Min = Min;
	m_Size = Size;

	// ��Ԑ����v�Z
	m_CellNum = (m_Pow[m_Level + 1] - 1) / 7;
	// ��ԃI�u�W�F�N�g�𐶐�
	delete[] m_TreeCellList;
	m_TreeCellList = new TreeCell<Collider3D>[m_CellNum];
	// �ŏ���Ԃ̋�ԃT�C�Y���v�Z
	m_Unit = m_Size / ((float)(1 << m_Level));

	// �ēo�^����
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
*	�R���W�����R���|�[�l���g�̏�����Ԃ̍X�V
*******************************************************************************/
void Collision3DManager::UpdateCells()
{
	for (auto itr = m_TreeCellDataList.begin(); itr != m_TreeCellDataList.end(); itr++)
	{
		// ��U������Ԃ��痣�E
		(*itr)->Remove();

		// �o�^����
		DWORD index = GetMortonNumber((*itr)->m_Object->GetMortonMinPos(), (*itr)->m_Object->GetMortonMaxPos());
		if (index < m_CellNum)
		{
			m_TreeCellList[index].Push((*itr));
		}
	}
}

/*******************************************************************************
*	�Փ˔���(�ċA����)
*******************************************************************************/
void Collision3DManager::CheckCollision(DWORD Index, list<Collider3D*>& Stack)
{
	TreeCellData<Collider3D>* baseData = m_TreeCellList[Index].GetDataList();
	TreeCellData<Collider3D>* pertnerData;
	list<Collider3D*> objList;
	int objCount = 0;

	// ��ԓ��̃I�u�W�F�N�g�ƏՓ˔��������
	while (baseData)
	{
		if (baseData->m_Object->GetActive())
		{		
			// ������Ԃ̃I�u�W�F�N�g�Ɣ���
			pertnerData = baseData->m_Next;
			while (pertnerData)
			{
				if (pertnerData->m_Object->GetActive())
				{
					baseData->m_Object->Collision(pertnerData->m_Object);
				}
				pertnerData = pertnerData->m_Next;
			}

			// �e�ɂ������Ԃ̃I�u�W�F�N�g���i�[�����X�^�b�N�Ɣ���
			for (auto pertnerDataItr = Stack.begin(); pertnerDataItr != Stack.end(); pertnerDataItr++)
			{
				if (!(*pertnerDataItr)->GetActive()) { continue; }

				baseData->m_Object->Collision((*pertnerDataItr));
			}
		}

		// �X�^�b�N�o�^�p�̃��X�g�ɒǉ�
		objList.push_back(baseData->m_Object);
		// ���̃f�[�^�֐i�߂�
		baseData = baseData->m_Next;
		objCount++;
	}
	// �X�^�b�N�ɘA��
	Stack.splice(Stack.end(), objList);

	// �q��Ԃ̏Փ˔����i�߂�
	DWORD ChildIndex = Index * 8 + 1;
	if (ChildIndex < m_CellNum)
	{
		for (int i = 0; i < 8; i++, ChildIndex++)
		{
			CheckCollision(ChildIndex, Stack);
		}
	}

	// �X�^�b�N���炱�̋�Ԃ̃I�u�W�F�N�g���O��
	auto itr = Stack.rbegin();
	for (int i = 0; i < objCount - 1; i++)
	{
		itr++;
	}
	Stack.erase(itr.base(), Stack.end());
}

/*******************************************************************************
*	�Փ˃R�[���o�b�N����
*******************************************************************************/
void Collision3DManager::CheckCallBack()
{
	for (TreeCellData<Collider3D>* c : m_TreeCellDataList)
	{
		c->m_Object->CheckCallBack();
	}
}

/*******************************************************************************
*	������Ԃ����[�g���ԍ��ŋ��߂�
*******************************************************************************/
DWORD Collision3DManager::GetMortonNumber(D3DXVECTOR3 Min, D3DXVECTOR3 Max)
{
	// �ŏ����x���ɂ����鏊����Ԃ��v�Z
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
*	���W�����`8���ؗv�f�ԍ��ϊ�
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
*	���W�����`8���ؗv�f�ԍ��ϊ�
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
*	�f�o�b�O�p�֐�
*******************************************************************************/
#ifdef _DEBUG
void Collision3DManager::InitDebug()
{
	//-------------------
	// �o�b�t�@�ݒ�
	//-------------------
	m_VertexNum = (m_Level + 2) * (m_Level + 2) * 3 * 2;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * m_VertexNum;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// ���ɕ��s�Ȑ��̐� * 3�� * 2���_
	VERTEX_3D* vertex = new VERTEX_3D[m_VertexNum];
	D3D11_SUBRESOURCE_DATA sd;
	CreateVertex(vertex);
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	// �o�b�t�@����
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// �V�F�[�_�[�ݒ�
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

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	Renderer::SetWorldMatrix(&world);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// �|���S���`��
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

	// X��
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

	// Y��
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

	// Z��
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
