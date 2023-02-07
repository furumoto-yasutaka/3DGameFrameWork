/*******************************************************************************
*
*	�^�C�g���F	�Q�[���I�u�W�F�N�g�N���X	[ gameObject.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "component.h"
#include "manager.h"

#include <unordered_map>
#include <list>
#include <vector>
#include <typeinfo>
#include <string>

class GameObject
{
public:
	// �e�I�u�W�F�N�g�ݒ莞�̎q�ɑ΂���I�v�V����
	enum class SetParentOption
	{
		Nothing		= 0,
		KeepPos		= 1 << 0,		// ���W���ێ�
		KeepScale	= 1 << 1,		// �g�k���ێ�
		All			= (1 << 2) - 1,
	};

private:
	unordered_multimap<string, GameObject*>::iterator m_MapIterator;	// �}�b�v�C�e���[�^�[
	list<GameObject*>::iterator m_OrderedListIterator;					// ���X�g�C�e���[�^�[

	// 0�F�`��𔺂�Ȃ�����
	// 1�F�X�N���v�g
	// 2�F3D�`��𔺂�����
	// 3�F2D�`��𔺂�����
	// 4�F����
	list<Component*>	m_ComponentList[(int)Component::ProcGroup::Length];	// �R���|�[�l���g���X�g
	GameObject*			m_Parent = NULL;		// �e�I�u�W�F�N�g
	list<GameObject*>	m_Child;				// �q�I�u�W�F�N�g

	bool				m_IsActive = true;		// �A�N�e�B�u�t���O
	bool				m_IsDestroy = false;	// �폜�t���O
	bool				m_IsStatic = false;		// �ÓI�t���O
	string				m_Name;					// �I�u�W�F�N�g��
	int					m_Layer;				// �R���W�������C���[
	int					m_Tag;					// �I�u�W�F�N�g�^�O
#ifdef _DEBUG
	static inline ID3D11Buffer* m_VertexBuffer = NULL;			// ���_�o�b�t�@
	static inline ID3D11VertexShader* m_VertexShader = NULL;	// ���_�V�F�[�_�[
	static inline ID3D11PixelShader* m_PixelShader = NULL;		// �s�N�Z���V�F�[�_�[
	static inline ID3D11InputLayout* m_VertexLayout = NULL;		// ���̓��C�A�E�g
#endif
public:	
	D3DXVECTOR3			m_LocalPosition;		// ���W
	D3DXQUATERNION		m_LocalRotation;		// ��]
	D3DXVECTOR3			m_LocalScale;			// �T�C�Y

public:
	void Init(string Name, int Layer, int Tag,
		unordered_multimap<string, GameObject*>::iterator MapItr,
		list<GameObject*>::iterator OrderedListItr);
	void LateInit();
	void Uninit();
	void Update(int Group);
	void LateUpdate(int Group);
	void Draw(int Group);

	// �R���|�[�l���g�̍폜�m�F
	void CheckComponentDestroy();

	// �}�g���N�X���擾
	D3DXMATRIX GetMatrix();

	// ���ʕ����̒P�ʃx�N�g�����擾
	D3DXVECTOR3 GetForward();

	// ������̒P�ʃx�N�g�����擾
	D3DXVECTOR3 GetUp();

	// �E�����̒P�ʃx�N�g�����擾
	D3DXVECTOR3 GetRight();

	// ���g�Ƃ��̎q�I�u�W�F�N�g�̍폜��\��
	void SetDestroy();

	// �폜����
	bool Destroy();

	/////////////////////////////
	//�@�����@�e�q�֌W�@�����@//
	
	// ���g�̃��[�J���}�g���N�X�̌��_�ɂ����郏�[���h�}�g���N�X(�e�̃��[���h�}�g���N�X)�擾
	D3DXMATRIX GetLocalMatrixOrigin();
	// ���[���h�}�g���N�X�擾
	D3DXMATRIX GetWorldMatrix(D3DXMATRIX Matrix = Math::GetMatrixIdentity());

	// ���g�̃��[�J�����W�̌��_�ɂ����郏�[���h���W(�e�̃��[���h���W)�擾
	D3DXVECTOR3 GetLocalPositionOrigin();
	// ���[���h���W�擾
	D3DXVECTOR3 GetWorldPosition(D3DXVECTOR3 Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	// ���[���h���W�ݒ�
	void SetWorldPosition(D3DXVECTOR3 Position);

	// ���g�̃��[�J�����[�e�[�V�����̌��_�ɂ����郏�[���h���[�e�[�V����(�e�̃��[���h���[�e�[�V����)�擾
	D3DXQUATERNION GetLocalRotationOrigin();
	// ���[���h���[�e�[�V�����擾
	D3DXQUATERNION GetWorldRotation(D3DXQUATERNION Rotation = Math::GetQuaternionIdentity());
	// ���[���h���[�e�[�V�����ݒ�
	void SetWorldRotation(D3DXQUATERNION Rotation);

	// ���g�̃��[�J���X�P�[���̌��_�ɂ����郏�[���h�X�P�[��(�e�̃��[���h�X�P�[��)�擾
	D3DXVECTOR3 GetLocalScaleOrigin();
	// ���[���h�X�P�[���擾
	D3DXVECTOR3 GetWorldScale(D3DXVECTOR3 Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	// ���[���h�X�P�[���ݒ�
	void SetWorldScale(D3DXVECTOR3 Scale);
	/////////////////////////////

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	unordered_multimap<string, GameObject*>::iterator GetMapIterator() { return m_MapIterator; }
	list<GameObject*>::iterator GetOrderedListIterator() { return m_OrderedListIterator; }
	void SetIterator(unordered_multimap<string, GameObject*>::iterator MapItr,
		list<GameObject*>::iterator OrderedListItr);

	list<Component*> GetComponentAll();

	GameObject* GetRoot();

	GameObject* GetParent() { return m_Parent; }
	void SetParent(GameObject* Parent,
		int RemoveOption = (int)SetParentOption::Nothing,
		int SetOption = (int)SetParentOption::Nothing);

	list<GameObject*> GetChildList() { return m_Child; }
	GameObject* GetChild(int index);

	bool GetActive();
	void SetActive(bool Value) { m_IsActive = Value; }

	bool GetIsDestroy() { return m_IsDestroy; }

	bool GetStatic() { return m_IsStatic; }
	void SetStatic(bool Value);

	string GetName() { return m_Name; }
	void SetName(string NewName);

	int GetLayer() { return m_Layer; }
	void AddLayer(int Layer) { m_Layer |= Layer; }

	int GetTag() { return m_Tag; }
	void AddTag(int Tag) { m_Tag |= Tag; }
	/////////////////////////////

private:
	void CheckRemoveOption(int Option, GameObject* Parent);
	void CheckSetOption(int Option, GameObject* Parent);

	/////////////////////////////////
	//�@�����@��{�ďo�֎~�@�����@//
public:
	// �q�I�u�W�F�N�g��ǉ��@����{�ďo�֎~
	void AddChild(GameObject* Child) { m_Child.push_back(Child); }
	// �q�I�u�W�F�N�g���폜�@����{�ďo�֎~
	void RemoveChild(GameObject* Child) { m_Child.remove(Child); }
	/////////////////////////////////


	/*******************************************************************************
	*	�R���|�[�l���g�ǉ�
	*******************************************************************************/
	template<class T>
	T* AddComponent()
	{
		T* component = DBG_NEW T(this);
		m_ComponentList[(int)component->GetProcGroup()].push_back(component);
		return component;
	}

	/*******************************************************************************
	*	�R���|�[�l���g�擾(�N���X���Q��)
	*******************************************************************************/
	template<class T>
	T* GetComponent()
	{
		for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
		{
			for (Component* c : m_ComponentList[i])
			{
				if (typeid(*c) == typeid(T))
				{
					return (T*)c;
				}
			}
		}
		return NULL;
	}

	/*******************************************************************************
	*	�R���|�[�l���g�S�擾(�N���X���Q��)
	*******************************************************************************/
	template<class T>
	vector<T*> GetComponents()
	{
		vector<T*> components;
		for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
		{
			for (Component* c : m_ComponentList[i])
			{
				if (typeid(*c) == typeid(T))
				{
					components.push_back(c);
				}
			}
		}
		return components;
	}

#ifdef _DEBUG
private:
	void InitDebug();
	void UninitDebug();
	void CreateVertex(VERTEX_3D* Vertex);
public:
	void DrawDebug();
#endif
};
