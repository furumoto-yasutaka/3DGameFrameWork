/*******************************************************************************
*
*	�^�C�g���F	�Q�[���I�u�W�F�N�g�N���X	[ gameObject.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "gameObject.h"
#include "component.h"
#include "manager.h"
#include "debugManager.h"

void GameObject::Init(string Name, int Layer, int Tag,
	unordered_multimap<string, GameObject*>::iterator MapItr,
	list<GameObject*>::iterator OrderedListItr)
{
	// ������
	m_Name = Name;
	m_Layer = Layer;
	m_Tag = Tag;
	m_MapIterator = MapItr;
	m_OrderedListIterator = OrderedListItr;
	m_LocalPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_LocalRotation = Math::GetQuaternionIdentity();
	m_LocalScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

#ifdef _DEBUG
	InitDebug();
#endif
}

void GameObject::LateInit()
{
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (Component* c : m_ComponentList[i])
		{
			c->LateInit();
		}
	}
}

void GameObject::Uninit()
{
	// �R���|�[�l���g��S�ĉ��
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (Component* c : m_ComponentList[i])
		{
			c->Uninit();
			delete c;
		}
		m_ComponentList[i].clear();
	}

	// ���g�Ɋւ���e�q�֌W��S�č폜
	SetParent(NULL);

	list<GameObject*> tempChild = m_Child;
	for (GameObject* obj : tempChild)
	{
		obj->SetParent(NULL);
	}

#ifdef _DEBUG
	UninitDebug();
#endif
}

void GameObject::Update(int Group)
{
	// ��A�N�e�B�u�̏ꍇ�͉��������I��
	if (!m_IsActive) { return; }

	for (Component* c : m_ComponentList[Group])
	{
		// �R���|�[�l���g����A�N�e�B�u�̏ꍇ�̓X�L�b�v����
		if (!c->GetActive()) { continue; }

		c->Update();
	}
}

void GameObject::LateUpdate(int Group)
{
	// ��A�N�e�B�u�̏ꍇ�͉��������I��
	if (!m_IsActive) { return; }

	for (Component* c : m_ComponentList[Group])
	{
		// �R���|�[�l���g����A�N�e�B�u�̏ꍇ�̓X�L�b�v����
		if (!c->GetActive()) { continue; }

		c->LateUpdate();
	}
}

void GameObject::Draw(int Group)
{
	// ��A�N�e�B�u�̏ꍇ�͉��������I��
	if (!m_IsActive) { return; }

	for (Component* c : m_ComponentList[Group])
	{
		// �R���|�[�l���g����A�N�e�B�u�̏ꍇ�̓X�L�b�v����
		if (!c->GetActive()) { continue; }

		c->Draw();
	}
}

/*******************************************************************************
*	�R���|�[�l���g�̍폜�m�F
*******************************************************************************/
void GameObject::CheckComponentDestroy()
{
	// �폜�\��̂������R���|�[�l���g���폜����
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		m_ComponentList[i].remove_if([](Component* component)
			{ return component->Destroy(); }
		);
	}
}

/*******************************************************************************
*	�e�I�u�W�F�N�g�ݒ�
*******************************************************************************/
void GameObject::SetParent(GameObject* Parent, int RemoveOption, int SetOption)
{
	// �O�̐e�I�u�W�F�N�g���玩�g�̏����폜
	if (m_Parent)
	{
		CheckRemoveOption(RemoveOption, m_Parent);

		m_Parent->RemoveChild(this);
	}

	// �V�����e�I�u�W�F�N�g�Ɏ��g�̏���o�^
	if (Parent)
	{
		CheckSetOption(SetOption, Parent);
		Parent->AddChild(this);
	}

	// �e��ύX
	m_Parent = Parent;
}

/*******************************************************************************
*	�}�g���N�X���擾
*******************************************************************************/
D3DXMATRIX GameObject::GetMatrix()
{
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_LocalScale.x, m_LocalScale.y, m_LocalScale.z);
	D3DXMatrixRotationQuaternion(&rot, &m_LocalRotation);
	D3DXMatrixTranslation(&trans, m_LocalPosition.x, m_LocalPosition.y, m_LocalPosition.z);
	return scale * rot * trans;
}

/*******************************************************************************
*	���ʕ����̒P�ʃx�N�g�����擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetForward()
{
	D3DXMATRIX rot;
	D3DXQUATERNION q = GetWorldRotation();
	D3DXMatrixRotationQuaternion(&rot, &q);

	D3DXVECTOR3 forward = { rot._31, rot._32, rot._33 };

	return forward;
}

/*******************************************************************************
*	������̒P�ʃx�N�g�����擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetUp()
{
	D3DXMATRIX rot;
	D3DXQUATERNION q = GetWorldRotation();
	D3DXMatrixRotationQuaternion(&rot, &q);

	D3DXVECTOR3 up = { rot._21, rot._22, rot._23 };

	return up;
}

/*******************************************************************************
*	�E�����̒P�ʃx�N�g�����擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetRight()
{
	D3DXMATRIX rot;
	D3DXQUATERNION q = GetWorldRotation();
	D3DXMatrixRotationQuaternion(&rot, &q);

	D3DXVECTOR3 right = { rot._11, rot._12, rot._13 };

	return right;
}

/*******************************************************************************
*	���g�Ƃ��̎q�I�u�W�F�N�g�̍폜��\��
*******************************************************************************/
void GameObject::SetDestroy()
{
	// ���g�̍폜��\��
	m_IsDestroy = true;

	// �q�I�u�W�F�N�g�̍폜��\��
	for (GameObject* obj : m_Child)
	{
		obj->SetDestroy();
	}
}

/*******************************************************************************
*	�폜����
*******************************************************************************/
bool GameObject::Destroy()
{
	if (m_IsDestroy)
	{
		Uninit();
		delete this;
		return true;
	}
	else
	{
		return false;
	}
}

/*******************************************************************************
*	���g�̃��[�J���}�g���N�X�̌��_�ɂ����郏�[���h�}�g���N�X
*	(�e�̃��[���h�}�g���N�X)�擾
*******************************************************************************/
D3DXMATRIX GameObject::GetLocalMatrixOrigin()
{
	// �e�����݂���ꍇ�ċA�I�Ƀ}�g���b�N�X�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldMatrix();
	}
	else
	{
		return Math::GetMatrixIdentity();
	}
}

/*******************************************************************************
*	���[���h�}�g���N�X�擾
*******************************************************************************/
D3DXMATRIX GameObject::GetWorldMatrix(D3DXMATRIX Matrix)
{
	// �e�����݂���ꍇ�ċA�I�Ƀ}�g���b�N�X�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldMatrix(Matrix * GetMatrix());
	}
	else
	{
		return Matrix * GetMatrix();
	}
}

/*******************************************************************************
*	���g�̃��[�J�����W�̌��_�ɂ����郏�[���h���W
*	(�e�̃��[���h���W)�擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetLocalPositionOrigin()
{
	// �e�����݂���ꍇ�ċA�I�ɍ��W�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

/*******************************************************************************
*	���[���h���W�擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetWorldPosition(D3DXVECTOR3 Position)
{
	// �e�����݂���ꍇ�ċA�I�ɍ��W�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldPosition(Position + m_LocalPosition);
	}
	else
	{
		return Position + m_LocalPosition;
	}
}

/*******************************************************************************
*	���[���h���W�ݒ�
*******************************************************************************/
void GameObject::SetWorldPosition(D3DXVECTOR3 Position)
{
	// �e�̃��[���h���W��������ċ��߂�
	if (m_Parent)
	{
		m_LocalPosition = Position - m_Parent->GetWorldPosition();
	}
	else
	{
		m_LocalPosition = Position;
	}
}

/*******************************************************************************
*	���g�̃��[�J�����[�e�[�V�����̌��_�ɂ����郏�[���h���[�e�[�V����
*	(�e�̃��[���h���[�e�[�V����)�擾
*******************************************************************************/
D3DXQUATERNION GameObject::GetLocalRotationOrigin()
{
	// �e�����݂���ꍇ�ċA�I�ɉ�]�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldRotation(Math::GetQuaternionIdentity());
	}
	else
	{
		return Math::GetQuaternionIdentity();
	}
}

/*******************************************************************************
*	���[���h���[�e�[�V�����擾
*******************************************************************************/
D3DXQUATERNION GameObject::GetWorldRotation(D3DXQUATERNION Rotation)
{
	// �e�����݂���ꍇ�ċA�I�ɉ�]�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldRotation(Rotation * m_LocalRotation);
	}
	else
	{
		return Rotation * m_LocalRotation;
	}
}

/*******************************************************************************
*	���[���h���[�e�[�V�����ݒ�
*******************************************************************************/
void GameObject::SetWorldRotation(D3DXQUATERNION Rotation)
{
	D3DXVECTOR3 euler = Math::QuaternionToEulerAngle(Rotation);
	D3DXVECTOR3 eulerParent = Math::QuaternionToEulerAngle(m_Parent->GetWorldRotation());

	// �e�̃��[���h�X�P�[����������ċ��߂�
	if (m_Parent)
	{
		m_LocalRotation = Math::EulerAngleToQuaternion(euler - eulerParent);
	}
	else
	{
		m_LocalRotation = Rotation;
	}
}

/*******************************************************************************
*	���g�̃��[�J���X�P�[���̌��_�ɂ����郏�[���h�X�P�[��
*	(�e�̃��[���h�X�P�[��)�擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetLocalScaleOrigin()
{
	// �e�����݂���ꍇ�ċA�I�Ɋg�k�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldScale(D3DXVECTOR3());
	}
	else
	{
		return D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
}

/*******************************************************************************
*	���[���h�X�P�[���擾
*******************************************************************************/
D3DXVECTOR3 GameObject::GetWorldScale(D3DXVECTOR3 Scale)
{
	D3DXVECTOR3 s = { Scale.x * m_LocalScale.x, Scale.y * m_LocalScale.y, Scale.z * m_LocalScale.z };

	// �e�����݂���ꍇ�ċA�I�Ɋg�k�����߂�
	if (m_Parent)
	{
		return m_Parent->GetWorldScale(s);
	}
	else
	{
		return s;
	}
}

/*******************************************************************************
*	���[���h�X�P�[���ݒ�
*******************************************************************************/
void GameObject::SetWorldScale(D3DXVECTOR3 Scale)
{
	// �e�̃��[���h�X�P�[����������ċ��߂�
	if (m_Parent)
	{
		m_LocalScale = Scale - m_Parent->GetWorldScale();
	}
	else
	{
		m_LocalScale = Scale;
	}
}

/*******************************************************************************
*	�I�u�W�F�N�g���X�g�̃C�e���[�^���㏑��
*******************************************************************************/
void GameObject::SetIterator(unordered_multimap<string, GameObject*>::iterator MapItr,
	list<GameObject*>::iterator OrderedListItr)
{
	m_MapIterator = MapItr;
	m_OrderedListIterator = OrderedListItr;
}

/*******************************************************************************
*	�S�ẴR���|�[�l���g���擾����
*******************************************************************************/
list<Component*> GameObject::GetComponentAll()
{
	list<Component*> result;
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (Component* c : m_ComponentList[i])
		{
			result.push_back(c);
		}
	}

	return result;
}

/*******************************************************************************
*	��Ԑe�̃I�u�W�F�N�g���擾
*******************************************************************************/
GameObject* GameObject::GetRoot()
{
	if (m_Parent)
	{
		return m_Parent->GetRoot();
	}
	else
	{
		return this;
	}
}

/*******************************************************************************
*	�q�I�u�W�F�N�g��Y�������w�肵�Ď擾
*******************************************************************************/
GameObject* GameObject::GetChild(int index)
{
	if (m_Child.size() < (unsigned int)index + 1)
	{
		return NULL;
	}

	auto itr = m_Child.begin();
	for (int i = 0; i < index; i++)
	{
		itr++;
	}

	return (*itr);
}

/*******************************************************************************
*	���g���A�N�e�B�u�ł��邩���擾
*******************************************************************************/
bool GameObject::GetActive()
{
	if (m_Parent)
	{
		return m_Parent->GetActive();
	}
	else
	{
		return m_IsActive;
	}
}

/*******************************************************************************
*	�I�u�W�F�N�g�̐ÓI�ݒ��ύX����
*******************************************************************************/
void GameObject::SetStatic(bool Value)
{
	if (m_IsStatic == Value) { return; }

	if (Value)
	{
		Manager::GetScene()->SetStatic(this);
	}
	else
	{
		Manager::GetScene()->SetDynamic(this);
	}
	
	m_IsStatic = Value;
}

/*******************************************************************************
*	�I�u�W�F�N�g�̖��O��ύX
*******************************************************************************/
void GameObject::SetName(string NewName)
{
	Manager::GetScene()->SetObjectName(this, NewName);
	m_Name = NewName;
}

void GameObject::CheckRemoveOption(int Option, GameObject* Parent)
{
	if (Option & (int)SetParentOption::KeepPos)
	{
		m_LocalPosition += Parent->GetWorldPosition();
	}
	if (Option & (int)SetParentOption::KeepScale)
	{
		D3DXVECTOR3 s = Parent->GetWorldScale();
		m_LocalScale = {
			m_LocalScale.x * s.x,
			m_LocalScale.y * s.y,
			m_LocalScale.z * s.z,
		};
	}
}

void GameObject::CheckSetOption(int Option, GameObject* Parent)
{
	if (Option & (int)SetParentOption::KeepPos)
	{
		D3DXMATRIX m = GetWorldMatrix();
		D3DXVECTOR3 thisPos = { m._41, m._42, m._43 };
		m = Parent->GetWorldMatrix();
		D3DXVECTOR3 parentPos = { m._41, m._42, m._43 };

		D3DXVECTOR3 pos = thisPos - parentPos;
		m_LocalPosition = pos.x * Parent->GetRight() + pos.y * Parent->GetUp() + pos.z * Parent->GetForward();
	}
	if (Option & (int)SetParentOption::KeepScale)
	{
		D3DXVECTOR3 s = Parent->GetWorldScale();
		m_LocalScale = {
			m_LocalScale.x / s.x,
			m_LocalScale.y / s.y,
			m_LocalScale.z / s.z,
		};
	}
}

/*******************************************************************************
*	�f�o�b�O�p�֐�
*******************************************************************************/
#ifdef _DEBUG
void GameObject::InitDebug()
{
	//-------------------
	// �o�b�t�@�ݒ�
	//-------------------
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VERTEX_3D) * 2;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	VERTEX_3D* vertex = new VERTEX_3D[2];
	CreateVertex(vertex);

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	// �o�b�t�@����
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// �V�F�[�_�[�ݒ�
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "debugLineVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "debugLinePS.cso");
}

void GameObject::UninitDebug()
{
	m_VertexBuffer->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_VertexLayout->Release();
}

void GameObject::DrawDebug()
{
	if (!DebugManager::m_IsParentLine || !m_Parent)
	{
		return;
	}

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ���[���h�}�g���N�X�ݒ�
	D3DXMATRIX world;
	world = Math::GetMatrixIdentity();
	Renderer::SetWorldMatrix(&world);

	// ���_��񏑂�����
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);
	CreateVertex((VERTEX_3D*)msr.pData);
	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	Renderer::SetMaterial(material);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(2, 0);
}

void GameObject::CreateVertex(VERTEX_3D* Vertex)
{
	D3DXMATRIX thisMat = GetWorldMatrix();
	D3DXMATRIX parentMat;
	if (m_Parent)
	{
		parentMat = m_Parent->GetWorldMatrix();
	}
	else
	{
		parentMat = thisMat;
	}

	D3DXVECTOR3 n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXCOLOR d = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	D3DXVECTOR2 c = D3DXVECTOR2(0.0f, 0.0f);

	Vertex[0].Position = D3DXVECTOR3(thisMat._41, thisMat._42, thisMat._43);
	Vertex[0].Normal = n;
	Vertex[0].Diffuse = d;
	Vertex[0].TexCoord = c;

	Vertex[1].Position = D3DXVECTOR3(parentMat._41, parentMat._42, parentMat._43);
	Vertex[1].Normal = n;
	Vertex[1].Diffuse = d;
	Vertex[1].TexCoord = c;
}
#endif
