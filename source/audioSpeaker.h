/*******************************************************************************
*
*	タイトル：	サウンド再生用コンポーネント	[ audioSpeaker.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "systemComponent.h"
#include "audio.h"

#include <list>
#include <string>
#include <map>

class AudioCallback;

class AudioSpeaker : public SystemComponent
{
public:
	// 再生用の情報をまとめた構造体
	struct PlayInfo
	{
		string					AudioName;			// サウンドの名称(コンテナ上の名前)
		AudioInfo*				AudioInfo;			// サウンドの詳細情報
		AudioInfo::AudioState	State;				// サウンドの状態
		bool					IsLoop;				// ループの有無
		IXAudio2SourceVoice*	SourceVoice;		// スピーカー

		// ストリーミング再生時のみ使用
		HMMIO*					Hmmio;				// 読み込み用ハンドル
		AudioCallback*			CallBack;			// コールバッククラス
		BYTE*					PrimaryBuffer;		// バッファ1
		BYTE*					SecondaryBuffer;	// バッファ2
		LONG					SecondaryBufLength;	// バッファ2のうち使用している領域
		LONG					SeekCursor;			// ファイルの読み込み位置
	};

private:
	static inline list<AudioSpeaker*>	m_SpeakerList;				// サウンドの全体操作用インスタンスリスト
	static inline const unsigned int	m_SECOND_PER_BUFFER = 1;	// ストリーミング再生用のバッファサイズをサウンドの何秒確保するか

	// ▼要素
	// 引数1	string型	識別キー(サウンド名称(連番))
	// 引数2	PlayInfo*型	再生情報
	map<string, PlayInfo*>	m_PlayInfo;		// 再生情報リスト

public:
	AudioSpeaker(GameObject* AttachObject) : SystemComponent(AttachObject)
	{
		m_SpeakerList.push_back(this);
	}
	~AudioSpeaker() { m_SpeakerList.remove(this); }

	void Init();
	void Uninit() override;
	void Update() override {}
	void Draw() override {}

	// 再生開始(戻り値は操作用の識別キー)
	string Play(string Name, bool IsLoop = false, float Volume = 1.0f);

	// 再生停止(キー参照)
	void Stop_FromKey(string Key);

	// 再生停止(名称参照 ※複数ある場合は現在再生中の中で最も連番が小さいサウンド)
	void Stop_FromAudioName(string Name);

	// 再生再開
	void Resume(string Key);

	// 一時停止
	void Pause(string Key);

	/////////////////////////////////////////////////
	//　↓↓　ストリーミング再生用メソッド　↓↓　//

	// 追加のバッファを読み込む
	void AddNextBuffer(string Key);

	// 再生情報を取得(キー参照)
	PlayInfo* GetPlayInfo_FromKey(string Key) { return m_PlayInfo[Key]; }

	/////////////////////////////////////////////////
private:
	// サウンドを登録
	PlayInfo* SetAudio(string Key, string Name, bool IsLoop);

	// 再生情報のイテレータを取得
	// (名称参照 ※複数ある場合は現在再生中の中で最も連番が小さいサウンド)
	map<string, PlayInfo*>::iterator GetIterator_FromAudioName(string Name);
	
	// 有効でないキーが渡された際のエラー処理
	void KeyUnknownError(string Key);

	// 再生情報リストに存在しないサウンド名称が渡された際のエラー処理
	void AudioNameUnknownError(string Name);

	/////////////////////////////////////////////////
	//　↓↓　ストリーミング再生用メソッド　↓↓　//
	
	// バッファサイズの標準値を取得
	LONG GetDefaultBufferLength(PlayInfo* Info);

	// ストリーミング用バッファを初期化
	void InitBuffer(PlayInfo* Info);

	// 確保可能なバッファサイズを計算
	LONG CalcBufferLength(PlayInfo* Info);

	// シーク位置が終端に達しているか確認する
	bool CheckSeek(PlayInfo* Info);
	/////////////////////////////////////////////////
};

//--------------------------------------------
// ストリーミング再生用コールバッククラス
//--------------------------------------------
class AudioCallback : public IXAudio2VoiceCallback
{
private:
	AudioSpeaker*	m_AudioSpeaker;	// スピーカー
	string			m_Key;			// スピーカーに登録されたサウンドの識別キー

public:
	AudioCallback(AudioSpeaker* AudioSpeaker, string Key)
		: m_AudioSpeaker(AudioSpeaker), m_Key(Key) {}
	// ????
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) {}
	// ????
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(void) {}
	// XAUDIO2_END_OF_STREAMフラグを立てた状態で
	// 現在のバッファの最後のバイトが消費された直後に呼び出される
	void STDMETHODCALLTYPE OnStreamEnd(void);
	// 現在のバッファの最初のバイトが消費される直前に呼び出される
	void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) {}
	// 現在のバッファの最後のバイトが消費された直後に呼び出される
	void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext);
	// ループの終了地点に達したときに呼び出される
	void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) {}
	// サウンドに何らかのエラーが発生した時に呼び出される(？)
	void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) {}
};
