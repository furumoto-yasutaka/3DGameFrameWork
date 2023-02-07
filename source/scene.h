/*******************************************************************************
*
*	�^�C�g���F	�V�[�����N���X	[ scene.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"

#include <unordered_map>
#include <list>
#include <vector>
#include <string>

class Camera;
class GameObject;
class Draw2DComponent;

class Scene
{
public:
	// �V�[���ʃr�b�g�t���O
	enum class SceneTag
	{
		Nothing					= 0,			// ��
		Demo_Invoke				= 1 << 0,
		Demo_CollisionSplit0	= 1 << 1,
		Demo_CollisionSplit1	= 1 << 2,
		Demo_Parent				= 1 << 3,
		Test					= 1 << 4,
		Everything				= (1 << 5) - 1,	// �S��
	};
	// �R���W�������C���[(�r�b�g�t���O)
	enum class ObjLayer
	{
		Default = 1 << 0,
	};
	// �I�u�W�F�N�g�^�O(�r�b�g�t���O)
	enum class ObjTag
	{
		Default			= 0,
		Player			= 1 << 0,
		Platform		= 1 << 1,
		Enemy			= 1 << 2,
		Everything		= (1 << 3) - 1,
	};
	static inline const bool CollisionFlag[3][3]
	{
		//Enemy		Platform	Player
		{ true,		true,		false	},	// Player
		{ true,		true,		true	},	// Platform
		{ true,		true,		true	},	// Enemy
	};

protected:
	unordered_multimap<string, GameObject*>			m_GameObject;				// ���I�I�u�W�F�N�g���X�g
	static inline unordered_multimap<string, GameObject*>	m_StaticGameObject;	// �ÓI�I�u�W�F�N�g���X�g
	SceneTag										m_Tag;						// ���g�̃V�[����\���^�O
	Camera*											m_ActiveCamera = NULL;		// ���ݗL���ɂȂ��Ă���J����
	
	list<GameObject*>								m_GameObject_Ordered;		// ���I�I�u�W�F�N�g���X�g(�D��x��)
	static inline list<GameObject*>					m_StaticGameObject_Ordered;	// �ÓI�I�u�W�F�N�g���X�g(�D��x��)
	
	list<Draw2DComponent*> m_Draw2DComponentList_PriorityOrdered;				// 2D�`��̕`�揇��\�����X�g

public:
	virtual void Init();
	void LateInit();
	void Uninit();
	virtual void Update();
	void Draw();

	// �I�u�W�F�N�g�폜�m�F
	void CheckObjectDestroy();

	// �I�u�W�F�N�g���V�[���ɒǉ�
	GameObject* AddGameObject(string Name, int Layer = (int)ObjLayer::Default, int Tag = (int)ObjTag::Default, bool IsStatic = false);

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//

	// �S�I�u�W�F�N�g�擾
	list<GameObject*> GetAllGameObject();
	// �I�u�W�F�N�g�擾(���̎Q��)
	GameObject* GetGameObject(string Name);
	// �I�u�W�F�N�g�S�擾(���̎Q��)
	vector<GameObject*> GetGameObjects(string Name);
	// �I�u�W�F�N�g�S�擾(���C���[�Q��)
	vector<GameObject*> GetGameObjectsFromLayer(int Layer);
	// �I�u�W�F�N�g�S�擾(�^�O�Q��)
	vector<GameObject*> GetGameObjectsFromTag(int Tag);

	int GetTag() { return (int)m_Tag; }

	Camera* GetActiveCamera() { return m_ActiveCamera; }
	void SetActiveCamera(Camera* ActiveCamera) { m_ActiveCamera = ActiveCamera; }
	/////////////////////////////


	/////////////////////////////////
	//�@�����@��{�ďo�֎~�@�����@//

	// �ÓI�I�u�W�F�N�g�ɕύX����
	void SetStatic(GameObject* Object);

	// ���I�I�u�W�F�N�g�ɕύX����
	void SetDynamic(GameObject* Object);

	// �I�u�W�F�N�g�̖��O(�L�[)��ύX����
	void SetObjectName(GameObject* Object, string NewName);

	// 2D�`��R���|�[�l���g���X�g�ɒǉ�����
	void AddDraw2DComponentList(Draw2DComponent* Component);

	// 2D�`��R���|�[�l���g���X�g��D��x���ɐ��񂷂�
	void SortDraw2DComponentList();
	/////////////////////////////////
private:
	// ���f���E�e�N�X�`�����̃��[�h
	void InitAsset();
};
