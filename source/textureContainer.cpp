/*******************************************************************************
*
*	�^�C�g���F	�e�N�X�`���Ǘ��p�ÓI�N���X	[ textureContainer.cpp ]
*	�� ���f���ɕt�����Ă���e�N�X�`���͊Ǘ��Ɋ܂݂܂���
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "textureContainer.h"
#include "manager.h"
#include "scene.h"

void TextureContainer::Init()
{
	// �Œ�A�Z�b�g
	AddTexture("Black", "Default\\black.png",
		1, 1, (int)Scene::SceneTag::Everything);

	AddTexture("White", "Default\\white.png",
		1, 1, (int)Scene::SceneTag::Everything);


	// Logo�V�[��
	AddTexture("DevelopLogo", "Logo\\Logo.png",
		1, 1, (int)Scene::SceneTag::Everything);

	// GameUi
	AddTexture("PlayerHp_Frame", "Game\\hartSub.png",
		1, 1, (int)Scene::SceneTag::Everything);
	AddTexture("PlayerHp_Inside", "Game\\hart.png",
		1, 1, (int)Scene::SceneTag::Everything);
}

void TextureContainer::Uninit()
{
	// ���ׂẴe�N�X�`�������
	for (auto itr : m_TextureInfo)
	{
		itr.second->Unload();
		delete itr.second;
	}
}

/*******************************************************************************
*	���ׂẴe�N�X�`���ɑ΂��Ďg�p�t���O�ɉ�����
*	���[�h�E�A�����[�h�����s(�V�[���ύX���p)
*******************************************************************************/
void TextureContainer::LoadAndUnload_AllTexture()
{
	for (auto itr = m_TextureInfo.begin(); itr != m_TextureInfo.end(); itr++)
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
*	�e�N�X�`���擾(���̂Ō���)
*******************************************************************************/
Texture* TextureContainer::GetTexture_InName(string Name)
{
	decltype(m_TextureInfo)::iterator itr = m_TextureInfo.find(Name);
	if (itr != m_TextureInfo.end())
	{
		return itr->second;
	}
	else
	{
		string str = string("���݂��Ȃ����̂̃e�N�X�`���̎擾���v������܂����B\n") + Name;
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("textureContainer:Error"),
			MB_OK | MB_ICONERROR);
		return NULL;
	}
}

/*******************************************************************************
*	�e�N�X�`���ǉ�
*******************************************************************************/
void TextureContainer::AddTexture(string Name, string Path, int WidthDiv, int HeightDiv, int Tag)
{
	string fullPath = "asset\\texture\\" + Path;

	// �v�f���}�b�v�ɑ��݂��邩�m�F
	if (m_TextureInfo.count(string(Name)))
	{
		string str = string("���łɑ��݂��閼�̂Ńe�N�X�`���̒ǉ����v������܂����B\n") + fullPath + "\n���̃e�N�X�`���͓ǂݍ��܂�܂���B";
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("textureContainer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_TextureInfo[Name] = DBG_NEW Texture(fullPath.c_str());
		m_TextureInfo[Name]->SetWidthDiv(WidthDiv);
		m_TextureInfo[Name]->SetHeightDiv(HeightDiv);
		m_TextureInfo[Name]->AddTag(Tag);
	}
}
