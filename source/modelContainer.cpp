/*******************************************************************************
*
*	�^�C�g���F	���f���Ǘ��p�ÓI�N���X	[ modelContainer.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "modelContainer.h"
#include "manager.h"
#include "scene.h"

void ModelContainer::Init()
{
	// �X�J�C�h�[���p
	AddModel("SkyDome", "SkyDome.obj", (int)Scene::SceneTag::Everything);

	// �v���C���[
	AddModel("Coconut",					"Game\\Coconut\\coconut.obj",				(int)Scene::SceneTag::Everything);
	AddModel("Player_Sphere",			"Game\\Player\\PlayerSphere.obj",			(int)Scene::SceneTag::Everything);
	AddModel("Player_Cover",			"Game\\Player\\PlayerCover.obj",			(int)Scene::SceneTag::Everything);
	AddModel("Player_RodConnection",	"Game\\Player\\PlayerRodConnection.obj",	(int)Scene::SceneTag::Everything);
	AddModel("Player_RodFirstHalf",		"Game\\Player\\PlayerRodFirstHalf.obj",		(int)Scene::SceneTag::Everything);
	AddModel("Player_RodLetterHalf",	"Game\\Player\\PlayerRodLetterHalf.obj",	(int)Scene::SceneTag::Everything);

	// �G�l�~�[
	AddModel("Enemy_Egg", "Game\\Egg\\egg.obj", (int)Scene::SceneTag::Everything);

	// �v���b�g�t�H�[��
	AddModel("Platform_Cube", "Game\\Platform\\Cube.obj", (int)Scene::SceneTag::Test);
}

void ModelContainer::Uninit()
{
	// ���ׂẴ��f�������
	for (auto itr : m_ModelInfo)
	{
		itr.second->Unload(true);
	}
	for (auto itr : m_ModelInfo)
	{
		if (itr.second) { delete itr.second; }
	}
}

/*******************************************************************************
*	���ׂẴ��f���ɑ΂��ă^�O�ɉ�����
*	���[�h�E�A�����[�h�����s(�V�[���ύX���p)
*******************************************************************************/
void ModelContainer::LoadAndUnload_AllModel()
{
	for (auto itr = m_ModelInfo.begin(); itr != m_ModelInfo.end(); itr++)
	{
		if (itr->second->GetTag() & Manager::GetScene()->GetTag())
		{// ���̃V�[���Ŏg���ꍇ
			itr->second->Load();
		}
		else
		{// ���̃V�[���Ŏg��Ȃ��ꍇ
			itr->second->Unload();
		}
	}
}

/*******************************************************************************
*	���f���擾(���̂Ō���)
*******************************************************************************/
Model* ModelContainer::GetModel_InName(string Name)
{
	decltype(m_ModelInfo)::iterator itr = m_ModelInfo.find(Name);
	if (itr != m_ModelInfo.end())
	{
		return itr->second;
	}
	else
	{
		string str = string("���݂��Ȃ����̂̃��f���̎擾���v������܂����B\n") + Name;
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("modelContainer:Error"),
			MB_OK | MB_ICONERROR);
		return NULL;
	}
}

/*******************************************************************************
*	���f���ǉ�
*******************************************************************************/
void ModelContainer::AddModel(string Name, string Path, int Tag)
{
	string fullPath = "asset\\model\\" + Path;

	// �v�f���}�b�v�ɑ��݂��邩�m�F
	if (m_ModelInfo.find(Name) != m_ModelInfo.end())
	{
		string str = string("���łɑ��݂��閼�̂Ń��f���̒ǉ����v������܂����B\n") + fullPath + "\n���̃��f���͓ǂݍ��܂�܂���B";
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("modelContainer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_ModelInfo[Name] = DBG_NEW Model(fullPath.c_str());
		m_ModelInfo[Name]->AddTag(Tag);
	}
}
