/*******************************************************************************
*
*	タイトル：	サウンドクラス	[ audio.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include <xaudio2.h>
#include <vector>

class AudioInfo
{
public:
	// サウンドの状態
	enum class AudioState
	{
		Play = 0,	// 再生中
		Pause,		// 再生停止
	};

private:
	char					m_Path[256];			// ファイルパス
	WAVEFORMATEX			m_WaveFormat;			// ファイル構成情報
	BYTE*					m_AudioData = NULL;		// ファイルデータ(ストリーミング再生時はなし)
	int						m_AudioBytes = 0;		// バイト数
	bool					m_IsStreaming = false;	// ストリーミング再生の有無
	float					m_Volume = 1.0f;		// サウンドのボリューム(0.0 ≦ 値)

public:
	AudioInfo() = delete;
	AudioInfo(const char* Path, float Volume)
	{
		strcpy(m_Path, Path);
		m_Volume = Volume;
	}

	// ロード
	void Load();

	// アンロード
	void Unload();

	// ファイルを開く(ストリーミング再生用)
	void Open(HMMIO* Hmmio);

	/////////////////////////////
	//　↓↓　アクセサ　↓↓　//
	char* GetPath() { return m_Path; }

	WAVEFORMATEX* GetWaveFormat() { return &m_WaveFormat; }

	BYTE* GetAudioData() { return m_AudioData; }

	int GetAudioBytes() { return m_AudioBytes; }

	bool GetIsStreaming() { return m_IsStreaming; }

	float GetVolume() { return m_Volume; }
	/////////////////////////////
};
