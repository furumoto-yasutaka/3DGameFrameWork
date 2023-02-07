/*******************************************************************************
*
*	タイトル：	サウンド管理用静的クラス	[ audioContainer.cpp ]
*
*	作成者：	古本 泰隆
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
*	マスタースピーカーの初期化
*******************************************************************************/
void AudioContainer::InitMaster()
{
	// COM初期化
	(void)CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio生成
	XAudio2Create(&m_Xaudio, 0);

	// マスタリングボイス生成
	m_Xaudio->CreateMasteringVoice(&m_MasteringVoice);
}

/*******************************************************************************
*	マスタースピーカーの終了処理
*******************************************************************************/
void AudioContainer::UninitMaster()
{
	m_MasteringVoice->DestroyVoice();
	m_Xaudio->Release();
	CoUninitialize();
}

/*******************************************************************************
*	サウンド情報取得(名称で検索)
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
		string str = string("存在しない名称のサウンドの取得が要求されました。\n") + Name;
		MessageBox(GetWindow(),
			TEXT(str.c_str()),
			TEXT("audioContainer:Error"),
			MB_OK | MB_ICONERROR);
		return NULL;
	}
}

/*******************************************************************************
*	サウンド名称(コンテナ上の名前)取得(インスタンス参照)
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

	string str = string("存在しないサウンドの名称の取得が要求されました。");
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("audioContainer:Error"),
		MB_OK | MB_ICONERROR);
	return "";
}

/*******************************************************************************
*	効果音追加
*******************************************************************************/
void AudioContainer::AddAudio(string Name, string Path, float Volume)
{
	string fullPath = "asset\\audio\\" + Path;

	// 要素がマップに存在するか確認
	if (m_AudioInfo.count(string(Name)))
	{
		string str = string("すでに存在する名称でサウンドの追加が要求されました。\n") + fullPath + "\nこのサウンドは読み込まれません。";
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
*	サウンド取得(パスで検索)
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
