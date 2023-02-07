/*******************************************************************************
*
*	�^�C�g���F	�V�[�����N���X	[ scene.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "scene.h"
#include "gameObject.h"
#include "draw2dComponent.h"
#include "modelContainer.h"
#include "textureContainer.h"
#include "audioContainer.h"
#include "skyDome.h"
#include "debugManager.h"

#include <typeinfo>
#include <algorithm>

void Scene::Init()
{
	InitAsset();
}

void Scene::LateInit()
{
	for (auto itr : m_GameObject_Ordered)
	{
		itr->LateInit();
	}
	for (auto itr : m_StaticGameObject_Ordered)
	{
		itr->LateInit();
	}
}

void Scene::Uninit()
{
	for (auto itr : m_GameObject_Ordered)
	{
		itr->Uninit();
		delete itr;
	}
	m_GameObject.clear();
	m_GameObject_Ordered.clear();
}

void Scene::Update()
{
	// �X�V����
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Update(i); }
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Update(i); }
		}
	}

	// �x���X�V����
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive())
			{
				itr->LateUpdate(i);
				itr->CheckComponentDestroy();
			}
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive())
			{
				itr->LateUpdate(i);
				itr->CheckComponentDestroy();
			}
		}
	}
}

void Scene::Draw()
{
	// �`�揈��
	for (int i = 0; i < (int)Component::ProcGroup::Length; i++)
	{
		// 2D�`��͍Ō�ɍs���̂ŃX�L�b�v����
		if (i == (int)Component::ProcGroup::Draw2D) { continue; }

		// �X�J�C�h�[���̕`���3D�`��ƈꏏ�ɍs��
		if (i == (int)Component::ProcGroup::Draw3D) { SkyDome::Draw(); }

		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Draw(i); }
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive()) { itr->Draw(i); }
		}
	}

#ifdef _DEBUG
	if (DebugManager::m_IsParentLine)
	{
		for (auto itr : m_GameObject_Ordered)
		{
			if (itr->GetActive()) { itr->DrawDebug(); }
		}
		for (auto itr : m_StaticGameObject_Ordered)
		{
			if (itr->GetActive()) { itr->DrawDebug(); }
		}
	}
#endif

	// 2D�`��̂ݕʓr�D��x���ōs��
	for (auto itr : m_Draw2DComponentList_PriorityOrdered)
	{
		// �R���|�[�l���g�̕`�揈���𒼐ڌĂԂ̂�Scene���ŗL����Ԃ̊m�F������
		if (!itr->GetActive() || !itr->GetAttachObject()->GetActive()) { continue; }
		itr->Draw();
	}
}

/*******************************************************************************
*	�I�u�W�F�N�g�폜�m�F
*******************************************************************************/
void Scene::CheckObjectDestroy()
{
	// ���I�I�u�W�F�N�g
	auto itr = m_GameObject_Ordered.begin();
	while (itr != m_GameObject_Ordered.end())
	{
		if ((*itr)->GetIsDestroy())
		{
			m_GameObject.erase((*itr)->GetMapIterator());
			(*itr)->Destroy();
			itr = m_GameObject_Ordered.erase(itr);
		}
		else { itr++; }
	}

	// �ÓI�I�u�W�F�N�g
	itr = m_StaticGameObject_Ordered.begin();
	while (itr != m_StaticGameObject_Ordered.end())
	{
		if ((*itr)->GetIsDestroy())
		{
			m_StaticGameObject.erase((*itr)->GetMapIterator());
			(*itr)->Destroy();
			itr = m_StaticGameObject_Ordered.erase(itr);
		}
		else { itr++; }
	}
}

/*******************************************************************************
*	�I�u�W�F�N�g���V�[���ɒǉ�
*******************************************************************************/
GameObject* Scene::AddGameObject(string Name, int Layer, int Tag, bool IsStatic)
{
	GameObject* gameObject = DBG_NEW GameObject();
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;
	
	// ���X�g�ɒǉ����A�C�e���[�^��ۑ�
	if (IsStatic)
	{// �ÓI�I�u�W�F�N�g�Ƃ��Ēǉ�
		mapItr = m_StaticGameObject.insert({ Name, gameObject });
		m_StaticGameObject_Ordered.push_back(gameObject);
		orderedListItr = m_StaticGameObject_Ordered.rbegin().base();
	}
	else
	{// ���I�I�u�W�F�N�g�Ƃ��Ēǉ�
		mapItr = m_GameObject.insert({ Name, gameObject });
		m_GameObject_Ordered.push_back(gameObject);
		orderedListItr = m_StaticGameObject_Ordered.rbegin().base();
	}

	gameObject->Init(Name, Layer, Tag, mapItr, orderedListItr);

	return gameObject;
}

/*******************************************************************************
*	�ÓI�I�u�W�F�N�g�ɕύX����
*******************************************************************************/
void Scene::SetStatic(GameObject* Object)
{
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;

	// �Y������I�u�W�F�N�g��ÓI�I�u�W�F�N�g�Ɉړ�����
	m_GameObject.erase(Object->GetMapIterator());
	m_GameObject_Ordered.erase(Object->GetOrderedListIterator());

	mapItr = m_StaticGameObject.insert({ Object->GetName(), Object });
	m_StaticGameObject_Ordered.push_back(Object);
	orderedListItr = m_StaticGameObject_Ordered.rbegin().base();

	Object->SetIterator(mapItr, orderedListItr);
}

/*******************************************************************************
*	���I�I�u�W�F�N�g�ɕύX����
*******************************************************************************/
void Scene::SetDynamic(GameObject* Object)
{
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;

	// �Y������I�u�W�F�N�g��ÓI�I�u�W�F�N�g�Ɉړ�����
	m_StaticGameObject.erase(Object->GetMapIterator());
	m_StaticGameObject_Ordered.erase(Object->GetOrderedListIterator());

	mapItr = m_GameObject.insert({ Object->GetName(), Object });
	m_GameObject_Ordered.push_back(Object);
	orderedListItr = m_GameObject_Ordered.rbegin().base();

	Object->SetIterator(mapItr, orderedListItr);
}

/*******************************************************************************
*	�I�u�W�F�N�g�̖��O(�L�[)��ύX����
*******************************************************************************/
void Scene::SetObjectName(GameObject* Object, string NewName)
{
	unordered_multimap<string, GameObject*>::iterator mapItr;
	list<GameObject*>::iterator orderedListItr;
	list<GameObject*>::iterator prevOrderedListItr;

	if (Object->GetStatic())
	{// �ÓI�I�u�W�F�N�g
		m_StaticGameObject.erase(Object->GetMapIterator());
		mapItr = m_StaticGameObject.insert({ NewName, Object });

		prevOrderedListItr = Object->GetOrderedListIterator();
		orderedListItr = m_StaticGameObject_Ordered.insert(prevOrderedListItr, Object);
		m_StaticGameObject_Ordered.erase(prevOrderedListItr);
	}
	else
	{// ���I�I�u�W�F�N�g
		m_StaticGameObject.erase(Object->GetMapIterator());
		mapItr = m_StaticGameObject.insert({ NewName, Object });

		prevOrderedListItr = Object->GetOrderedListIterator();
		orderedListItr = m_StaticGameObject_Ordered.insert(prevOrderedListItr, Object);
		m_StaticGameObject_Ordered.erase(prevOrderedListItr);
	}

	Object->SetIterator(mapItr, orderedListItr);
}

/*******************************************************************************
*	2D�`��R���|�[�l���g���X�g�ɒǉ�����
*******************************************************************************/
void Scene::AddDraw2DComponentList(Draw2DComponent* Component)
{
	m_Draw2DComponentList_PriorityOrdered.push_back(Component);

	// �D��x���ɐ��񂷂�
	SortDraw2DComponentList();
}

/*******************************************************************************
*	2D�`��R���|�[�l���g���X�g��D��x���ɐ��񂷂�
*******************************************************************************/
void Scene::SortDraw2DComponentList()
{
	// �D��x���ɂȂ�悤���ѕς���
	m_Draw2DComponentList_PriorityOrdered.sort([](auto const& lhs, auto const& rhs) {
			return lhs->GetDrawPriority() > lhs->GetDrawPriority();
		});
}

#pragma region GetGameObject
/*******************************************************************************
*	�S�I�u�W�F�N�g�擾
*******************************************************************************/
list<GameObject*> Scene::GetAllGameObject()
{
	list<GameObject*> list;

	list = m_GameObject_Ordered;
	list.splice(list.end(), m_StaticGameObject_Ordered);

	return list;
}

/*******************************************************************************
*	�I�u�W�F�N�g�擾(���̎Q��)
*******************************************************************************/
GameObject* Scene::GetGameObject(string Name)
{
	// ���I�I�u�W�F�N�g�Ŗ��O����v����C�e���[�^�����ׂĎ擾
	auto range = m_GameObject.equal_range(Name);
	// �P�ł�����������ŏ��̃C�e���[�^�̗v�f��Ԃ�
	if (range.first != m_GameObject.end())
	{
		return range.first->second;
	}

	// �ÓI�I�u�W�F�N�g�Ŗ��O����v����C�e���[�^�����ׂĎ擾
	range = m_StaticGameObject.equal_range(Name);
	// �P�ł�����������ŏ��̃C�e���[�^�̗v�f��Ԃ�
	if (range.first != m_StaticGameObject.end())
	{
		return range.first->second;
	}
	
	return NULL;
}

/*******************************************************************************
*	�I�u�W�F�N�g�S�擾(���̎Q��)
*******************************************************************************/
vector<GameObject*> Scene::GetGameObjects(string Name)
{
	vector<GameObject*> objects;

	// ���I�I�u�W�F�N�g�Ŗ��O����v����C�e���[�^�����ׂĎ擾
	auto range = m_GameObject.equal_range(Name);
	// �����������ׂĂ̗v�f�����X�g�Ɋi�[����
	if (range.first != m_GameObject.end())
	{
		for_each(range.first, range.second, [&objects](std::pair<string, GameObject*> itr)
			{ objects.push_back(itr.second); }
		);
	}

	// �ÓI�I�u�W�F�N�g�Ŗ��O����v����C�e���[�^�����ׂĎ擾
	range = m_StaticGameObject.equal_range(Name);
	// �����������ׂĂ̗v�f�����X�g�Ɋi�[����
	if (range.first != m_StaticGameObject.end())
	{
		for_each(range.first, range.second, [&objects](std::pair<string, GameObject*> itr)
			{ objects.push_back(itr.second); }
		);
	}

	return objects;
}

/*******************************************************************************
*	�I�u�W�F�N�g�S�擾(���C���[�Q��)
*******************************************************************************/
vector<GameObject*> Scene::GetGameObjectsFromLayer(int Layer)
{
	vector<GameObject*> objects;

	// ���C���[����v�������ׂẴI�u�W�F�N�g��Ԃ�
	for (auto itr : m_GameObject_Ordered)
	{
		if (itr->GetLayer() & Layer) { objects.push_back(itr); }
	}
	for (auto itr : m_StaticGameObject_Ordered)
	{
		if (itr->GetLayer() & Layer) { objects.push_back(itr); }
	}

	return objects;
}

/*******************************************************************************
*	�I�u�W�F�N�g�S�擾(�^�O�Q��)
*******************************************************************************/
vector<GameObject*> Scene::GetGameObjectsFromTag(int Tag)
{
	vector<GameObject*> objects;

	// �^�O����v�������ׂẴI�u�W�F�N�g��Ԃ�
	for (auto itr : m_GameObject_Ordered)
	{
		if (itr->GetTag() & Tag) { objects.push_back(itr); }
	}
	for (auto itr : m_StaticGameObject_Ordered)
	{
		if (itr->GetTag() & Tag) { objects.push_back(itr); }
	}

	return objects;
}
#pragma endregion

/*******************************************************************************
*	���f���E�e�N�X�`�����̃��[�h
*******************************************************************************/
void Scene::InitAsset()
{
	// ���f��
	ModelContainer::LoadAndUnload_AllModel();

	// �e�N�X�`��
	TextureContainer::LoadAndUnload_AllTexture();
}
