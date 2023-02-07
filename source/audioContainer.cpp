/*******************************************************************************
*
*	�^�C�g���F	�T�E���h�Ǘ��p�ÓI�N���X	[ audioContainer.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "audioContainer.h"
#include "scene.h"
#include "manager.h"

void AudioContainer::Init()
{
	InitMaster();

	// BGM
	AddAudio("TestBgm", "Bgm\\TitleBgm.wav", 0.2f);
	AddAudio("TestBgm2", "Bgm\\GameBgm.wav", 0.2f);
	AddAudio("TestBgm3", "Bgm\\StageSelectBgm.wav", 0.2f);
	AddAudio("TestBgm4", "Bgm\\ResultBgm.wav", 0.2f);

	// SE
}

void AudioContainer::Uninit()
{
	for (auto itr = m_AudioInfo.begin(); itr != m_AudioInfo.end(); itr++)
	{
		itr->second->Unload();
		delete itr->second;
	}

	UninitMaster();
}

/*******************************************************************************
*	�}�X�^�[�X�s�[�J�[�̏�����
*******************************************************************************/
void AudioContainer::InitMaster()
{
	// COM������
	(void)CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
	XAudio2Create(&m_Xaudio, 0);

	// �}�X�^�����O�{�C�X����
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}

/*******************************************************************************
*	�}�X�^�[�X�s�[�J�[�̏I������
*******************************************************************************/
void AudioContainer::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}

/*******************************************************************************
*	�T�E���h���擾(���̂Ō���)
*******************************************************************************/
AudioInfo* AudioContainer::GetAudio_InName(string Name)
{
	decltype(m_AudioInfo)::iterator itr = m_AudioInfo.find(Name);
	if (itr != m_AudioInfo.end())
	{
		return itr->second;
	}
	else
	{
		string str = string("���݂��Ȃ����̂̃T�E���h�̎擾���v������܂����B\n") + Name;
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("audioContainer:Error"),
			MB_OK | MB_ICONERROR);
		return NULL;
	}
}

/*******************************************************************************
*	�T�E���h����(�R���e�i��̖��O)�擾(�C���X�^���X�Q��)
*******************************************************************************/
string AudioContainer::GetName_InAudio(AudioInfo* Info)
{
	for (auto itr = m_AudioInfo.begin(); itr != m_AudioInfo.end(); itr++)
	{
		if (itr->second == Info)
		{
			return itr->first;
		}
	}

	string str = string("���݂��Ȃ��T�E���h�̖��̂̎擾���v������܂����B");
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("audioContainer:Error"),
		MB_OK | MB_ICONERROR);
	return "";
}

/*******************************************************************************
*	���ʉ��ǉ�
*******************************************************************************/
void AudioContainer::AddAudio(string Name, string Path, float Volume)
{
	string fullPath = "asset\\audio\\" + Path;

	// �v�f���}�b�v�ɑ��݂��邩�m�F
	if (m_AudioInfo.count(string(Name)))
	{
		string str = string("���łɑ��݂��閼�̂ŃT�E���h�̒ǉ����v������܂����B\n") + fullPath + "\n���̃T�E���h�͓ǂݍ��܂�܂���B";
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("audioContainer:Error"),
			MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_AudioInfo[Name] = CreateAudio_InPath(fullPath, Volume);
		m_AudioInfo[Name]->Load();
	}
}

/*******************************************************************************
*	�T�E���h�擾(�p�X�Ō���)
*******************************************************************************/
AudioInfo* AudioContainer::CreateAudio_InPath(string Path, float Volume)
{
	for (auto itr = m_AudioInfo.begin(); itr != m_AudioInfo.end(); itr++)
	{
		if (strcmp(itr->second->GetPath(), Path.c_str()) == 0)
		{
			return itr->second;
		}
	}

	return DBG_NEW AudioInfo(Path.c_str(), Volume);
}
