/*******************************************************************************
*
*	タイトル：	サウンド再生用コンポーネント	[ audioSpeaker.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "audioSpeaker.h"
#include "audioContainer.h"
#include "uniqueNamingSystem.h"

void AudioSpeaker::Init()
{
	m_SpeakerList.push_back(this);
}

void AudioSpeaker::Uninit()
{
	for (auto itr = m_PlayInfo.begin(); itr != m_PlayInfo.end(); itr++)
	{
		PlayInfo* info = itr->second;

		// サウンドを停止し解放
		if (info->SourceVoice)
		{
			info->SourceVoice->Stop();
			info->SourceVoice->DestroyVoice();
		}
		// ストリーミング用の要素を解放
		if (info->AudioInfo->GetIsStreaming())
		{
			mmioClose(*info->Hmmio, 0);
			delete info->CallBack;
			delete info->PrimaryBuffer;
			delete info->SecondaryBuffer;
		}

		delete info;
	}
	
	m_SpeakerList.remove(this);
}

/*******************************************************************************
*	再生開始(戻り値は操作用の識別キー)
*******************************************************************************/
string AudioSpeaker::Play(string Name, bool IsLoop, float Volume)
{
	string Key = UniqueNamingSystem::CreateUniqueName<PlayInfo*>(Name, m_PlayInfo);
	PlayInfo* info = SetAudio(Key, Name, IsLoop);

	if (info->AudioInfo->GetIsStreaming())
	{// ストリーミング再生
		InitBuffer(info);
	}
	else
	{// 通常再生
		// オーディオバッファ設定
		XAUDIO2_BUFFER bufinfo;
		memset(&bufinfo, 0x00, sizeof(bufinfo));
		bufinfo.AudioBytes = info->AudioInfo->GetAudioBytes();
		bufinfo.pAudioData = info->AudioInfo->GetAudioData();

		// ループ設定
		if (IsLoop)
		{
			bufinfo.LoopBegin = 0;
			bufinfo.LoopLength = info->AudioInfo->GetAudioBytes() / info->AudioInfo->GetWaveFormat()->nBlockAlign;
			bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
		}

		// バッファを反映
		info->SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);
	}

	// 再生開始
	info->SourceVoice->SetVolume(info->AudioInfo->GetVolume() * Volume);
	info->SourceVoice->Start();
	info->State = AudioInfo::AudioState::Play;

	return Key;
}

/*******************************************************************************
*	再生停止(キー参照)
*******************************************************************************/
void AudioSpeaker::Stop_FromKey(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// キーが有効か確認
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;

	// サウンドを停止し解放
	info->SourceVoice->Stop();
	info->SourceVoice->DestroyVoice();
	// ストリーミング用の要素を解放
	if (info->AudioInfo->GetIsStreaming())
	{
		mmioClose(*info->Hmmio, 0);
		delete info->CallBack;
		delete info->PrimaryBuffer;
		delete info->SecondaryBuffer;
	}
	delete info;
	
	// 再生情報リストから削除
	m_PlayInfo.erase(Key);
}

/*******************************************************************************
*	再生停止(名称参照 ※複数ある場合は現在再生中の中で最も連番が小さいサウンド)
*******************************************************************************/
void AudioSpeaker::Stop_FromAudioName(string Name)
{
	auto itr = GetIterator_FromAudioName(Name);
	// 同じサウンド名称の再生情報が存在するか確認
	if (itr == m_PlayInfo.end())
	{
		AudioNameUnknownError(Name);
		return;
	}

	PlayInfo* info = itr->second;

	// サウンドを停止し解放
	info->SourceVoice->Stop();
	info->SourceVoice->DestroyVoice();
	// ストリーミング用の要素を解放
	if (info->AudioInfo->GetIsStreaming())
	{
		mmioClose(*info->Hmmio, 0);
		delete info->CallBack;
		delete info->PrimaryBuffer;
		delete info->SecondaryBuffer;
	}
	delete info;

	// 再生情報リストから削除
	m_PlayInfo.erase(itr);
}

/*******************************************************************************
*	再生再開
*******************************************************************************/
void AudioSpeaker::Resume(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// キーが有効か確認
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;
	// 再生停止中でない場合は終了
	if (info->State != AudioInfo::AudioState::Pause) { return; }

	// 再生開始
	info->SourceVoice->SetVolume(info->AudioInfo->GetVolume());
	info->SourceVoice->Start();
	info->State = AudioInfo::AudioState::Play;
}

/*******************************************************************************
*	一時停止
*******************************************************************************/
void AudioSpeaker::Pause(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// キーが有効か確認
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;
	// 再生中でない場合は終了
	if (info->State != AudioInfo::AudioState::Play) { return; }

	// 再生停止
	info->SourceVoice->Stop();
	info->State = AudioInfo::AudioState::Pause;
}

/*******************************************************************************
*	追加のバッファを読み込む
*******************************************************************************/
void AudioSpeaker::AddNextBuffer(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// キーが有効か確認
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;
	bool endOfSteramFlag = CheckSeek(info);
	// ループ無しの設定でデータの終端に達している場合は
	// 追加の必要はない為終了する
	if (endOfSteramFlag && !info->IsLoop) { return; }

	//------------------------
	// データバッファ入れ替え
	//------------------------
	BYTE* temp = info->PrimaryBuffer;
	LONG primaryBufLength;

	info->PrimaryBuffer = info->SecondaryBuffer;
	info->SecondaryBuffer = temp;
	primaryBufLength = info->SecondaryBufLength;

	//------------------------
	// データバッファ読み込み
	//------------------------
	info->SecondaryBufLength = mmioRead(*info->Hmmio, (HPSTR)info->SecondaryBuffer, CalcBufferLength(info));
	info->SeekCursor += info->SecondaryBufLength;

	//------------------------
	// オーディオバッファ設定
	//------------------------
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = primaryBufLength;
	bufinfo.pAudioData = info->PrimaryBuffer;
	if (endOfSteramFlag)
	{
		// データの終端の場合は終了フラグを渡す
		bufinfo.Flags = XAUDIO2_END_OF_STREAM;
	}

	// バッファを反映
	info->SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);
}

/*******************************************************************************
*	サウンドを登録
*******************************************************************************/
AudioSpeaker::PlayInfo* AudioSpeaker::SetAudio(string Key, string Name, bool IsLoop)
{
	PlayInfo* info = new PlayInfo();

	info->AudioName = Name;
	info->AudioInfo = AudioContainer::GetAudio_InName(Name);
	info->State = AudioInfo::AudioState::Play;
	info->IsLoop = IsLoop;

	// ストリーミング再生用
	if (info->AudioInfo->GetIsStreaming())
	{
		info->Hmmio = new HMMIO();
		info->AudioInfo->Open(info->Hmmio);
		info->CallBack = new AudioCallback(this, Key);
		info->PrimaryBuffer = new unsigned char[GetDefaultBufferLength(info)];
		info->SecondaryBuffer = new unsigned char[GetDefaultBufferLength(info)];
		info->SecondaryBufLength = 0;
		info->SeekCursor = 0;
	}

	// サウンドソース生成
	AudioContainer::GetXaudio()->CreateSourceVoice(
		&info->SourceVoice,
		info->AudioInfo->GetWaveFormat(),
		0,
		XAUDIO2_DEFAULT_FREQ_RATIO,
		info->AudioInfo->GetIsStreaming() ? info->CallBack : NULL);
	assert(info->SourceVoice);

	// 再生情報をリストに追加
	m_PlayInfo[Key] = info;

	return info;
}

/*******************************************************************************
*	再生情報のイテレータを取得
* 	(名称参照 ※複数ある場合は現在再生中の中で最も連番が小さいサウンド)
*******************************************************************************/
map<string, AudioSpeaker::PlayInfo*>::iterator AudioSpeaker::GetIterator_FromAudioName(string Name)
{
	auto itr = m_PlayInfo.begin();

	for (; itr != m_PlayInfo.end() && itr->second->AudioName != Name; itr++);

	return itr;
}

/*******************************************************************************
*	有効でないキーが渡された際のエラー処理
*******************************************************************************/
void AudioSpeaker::KeyUnknownError(string Key)
{
	string str = string("存在しないキーでの参照が要求されました。\n") + Key;
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("audioSpeaker:Error"),
		MB_OK | MB_ICONERROR);
}

/*******************************************************************************
*	再生情報リストに存在しないサウンド名称が渡された際のエラー処理
*******************************************************************************/
void AudioSpeaker::AudioNameUnknownError(string Name)
{
	string str = string("再生情報リストに存在しないサウンド名称での参照が要求されました。\n") + Name;
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("audioSpeaker:Error"),
		MB_OK | MB_ICONERROR);
}

/*******************************************************************************
*	バッファサイズの標準値を取得
*******************************************************************************/
LONG AudioSpeaker::GetDefaultBufferLength(PlayInfo* Info)
{
	// 1秒あたりのバイト数　＊　バッファあたりの秒数
	return Info->AudioInfo->GetWaveFormat()->nAvgBytesPerSec * m_SECOND_PER_BUFFER;
}

/*******************************************************************************
*	ストリーミング用バッファを初期化
*******************************************************************************/
void AudioSpeaker::InitBuffer(PlayInfo* Info)
{
	//------------------------
	// データバッファ読み込み
	//------------------------
	LONG primaryBufLength;
	bool endOfSteramFlag = false;

	primaryBufLength = mmioRead(*Info->Hmmio, (HPSTR)Info->PrimaryBuffer, CalcBufferLength(Info));
	Info->SeekCursor += primaryBufLength;

	endOfSteramFlag = CheckSeek(Info);
	if (!endOfSteramFlag || Info->IsLoop)
	{
		Info->SecondaryBufLength = mmioRead(*Info->Hmmio, (HPSTR)Info->SecondaryBuffer, CalcBufferLength(Info));
		Info->SeekCursor += Info->SecondaryBufLength;
	}

	//------------------------
	// オーディオバッファ設定
	//------------------------
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = primaryBufLength;
	bufinfo.pAudioData = Info->PrimaryBuffer;
	if (endOfSteramFlag)
	{
		// データの終端の場合は終了フラグを渡す
		bufinfo.Flags = XAUDIO2_END_OF_STREAM;
	}

	// バッファを反映
	Info->SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);
}

/*******************************************************************************
*	確保可能なバッファサイズを計算
*******************************************************************************/
LONG AudioSpeaker::CalcBufferLength(PlayInfo* Info)
{
	LONG defaultLen = GetDefaultBufferLength(Info);
	LONG audioBytes = Info->AudioInfo->GetAudioBytes();

	// 残りのサウンドデータ量よりバッファサイズの方が大きいかどうか
	if (audioBytes - Info->SeekCursor < defaultLen)
	{// 大きい場合
		// 残りのサウンドデータ量を返す
		return audioBytes - Info->SeekCursor;
	}
	else
	{// 大きくない場合
		// バッファサイズを返す
		return defaultLen;
	}
}

/*******************************************************************************
*	シーク位置が終端に達しているか確認する
*******************************************************************************/
bool AudioSpeaker::CheckSeek(PlayInfo* Info)
{
	LONG audioBytes = Info->AudioInfo->GetAudioBytes();

	// データの終端まで読み込みが終了しているかどうか
	if (Info->SeekCursor >= audioBytes)
	{
		if (Info->IsLoop)
		{
			// 最後まで読み込み済みの場合はシークを先頭に戻しループに備える
			mmioSeek(*Info->Hmmio, -Info->SeekCursor, SEEK_CUR);
			Info->SeekCursor = 0;
		}
		return true;
	}
	else
	{
		return false;
	}
}


//　↓↓　コールバッククラスのメソッド　↓↓

/*******************************************************************************
*	XAUDIO2_END_OF_STREAMフラグを立てた状態で
* 	現在のバッファの最後のバイトが消費された直後に呼び出される
*******************************************************************************/
void AudioCallback::OnStreamEnd()
{
	// ループ設定ではない場合停止する
	if (!m_AudioSpeaker->GetPlayInfo_FromKey(m_Key)->IsLoop)
	{
		m_AudioSpeaker->Stop_FromKey(m_Key);
	}
}

/*******************************************************************************
*	現在のバッファの最後のバイトが消費された直後に呼び出される
*******************************************************************************/
void AudioCallback::OnBufferEnd(void* pBufferContext)
{
	m_AudioSpeaker->AddNextBuffer(m_Key);
}
