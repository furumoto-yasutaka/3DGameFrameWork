/*******************************************************************************
*
*	タイトル：	サウンド管理用静的クラス	[ audioContainer.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "audio.h"

#include <unordered_map>
#include <list>

class AudioContainer
{
private:
	// ▼要素
	// 引数1	string型		サウンド名称(キー)
	// 引数2	AudioInfo*型	サウンド情報
	static inline unordered_map<string, AudioInfo*> m_AudioInfo;		// サウンドリスト

	static inline IXAudio2*					m_Xaudio = NULL;			// XAudio2のインターフェース
	static inline IXAudio2MasteringVoice*	m_MasteringVoice = NULL;	// マスタースピーカー

public:
	static void Init();
	static void Uninit();

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	
	// サウンド情報取得(名称で検索)
	static AudioInfo* GetAudio_InName(string Name);

	// サウンド名称(コンテナ上の名前)取得(インスタンス参照)
	static string GetName_InAudio(AudioInfo* Info);

	static IXAudio2* GetXaudio() { return m_Xaudio; }
	/////////////////////////////
private:
	// マスタースピーカーの初期化
	static void InitMaster();

	// マスタースピーカーの終了処理
	static void UninitMaster();

	// 音追加
	static void AddAudio(string Name, string Path, float Volume);

	// サウンド取得(パスで検索)　※なければ新しく生成
	static AudioInfo* CreateAudio_InPath(string Path, float Volume);
};
