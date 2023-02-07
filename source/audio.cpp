/*******************************************************************************
*
*	タイトル：	サウンドクラス	[ audio.cpp ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#include "main.h"
#include "audioContainer.h"
#include "audioSpeaker.h"

#include <vector>

/*******************************************************************************
*	ロード
*******************************************************************************/
void AudioInfo::Load()
{
	HMMIO hmmio;
	MMIOINFO mmioinfo = { 0 };
	MMCKINFO riffchunkinfo = { 0 };
	MMCKINFO datachunkinfo = { 0 };
	MMCKINFO mmckinfo = { 0 };
	UINT32 buflen;

	// wavファイルを開く
	hmmio = mmioOpen((LPSTR)m_Path, &mmioinfo, MMIO_READ);
	assert(hmmio);

	// waveチャンクを読み込む
	riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

	// fmtチャンクを読み込む
	mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);
	if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
	{
		mmioRead(hmmio, (HPSTR)&m_WaveFormat, sizeof(m_WaveFormat));
	}
	else
	{
		PCMWAVEFORMAT pcmwf = { 0 };
		mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
		memset(&m_WaveFormat, 0x00, sizeof(m_WaveFormat));
		memcpy(&m_WaveFormat, &pcmwf, sizeof(pcmwf));
		m_WaveFormat.cbSize = 0;
	}
	mmioAscend(hmmio, &mmckinfo, 0);

	// dataチャンクを読み込む
	datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);
	buflen = datachunkinfo.cksize;

	// データ読み込み(ストリーミング再生の場合はこの部分をロード時には行わず切り離す)
	// データサイズが1MB未満の場合即時読み込む
	if (datachunkinfo.cksize < (DWORD)1000 * 1000)
	{
		m_AudioData = new unsigned char[buflen];
		m_AudioBytes = mmioRead(hmmio, (HPSTR)m_AudioData, buflen);
	}
	else
	{
		m_AudioBytes = buflen;
		// メモリ節約のためストリーミング再生で行う
		m_IsStreaming = true;
	}

	// waveファイルを閉じる
	mmioClose(hmmio, 0);
}

/*******************************************************************************
*	アンロード
*******************************************************************************/
void AudioInfo::Unload()
{
	delete[] m_AudioData;
}

/*******************************************************************************
*	ファイルを開く(ストリーミング再生用)
*******************************************************************************/
void AudioInfo::Open(HMMIO* Hmmio)
{
	MMIOINFO mmioinfo = { 0 };
	MMCKINFO riffchunkinfo = { 0 };
	MMCKINFO datachunkinfo = { 0 };
	MMCKINFO mmckinfo = { 0 };
	WAVEFORMATEX wfe;

	// waveファイルを開く
	*Hmmio = mmioOpen((LPSTR)m_Path, &mmioinfo, MMIO_READ);
	assert(*Hmmio);

	// waveチャンクを読み込む
	riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(*Hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

	// fmtチャンクを読み込む
	mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(*Hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

	if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
	{
		mmioRead(*Hmmio, (HPSTR)&wfe, sizeof(wfe));
	}
	else
	{
		PCMWAVEFORMAT pcmwf = { 0 };
		mmioRead(*Hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
	}
	mmioAscend(*Hmmio, &mmckinfo, 0);

	// dataチャンクを読み込む
	datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(*Hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);
}
