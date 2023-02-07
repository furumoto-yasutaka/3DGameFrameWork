/*******************************************************************************
*
*	�^�C�g���F	�T�E���h�Đ��p�R���|�[�l���g	[ audioSpeaker.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
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

		// �T�E���h���~�����
		if (info->SourceVoice)
		{
			info->SourceVoice->Stop();
			info->SourceVoice->DestroyVoice();
		}
		// �X�g���[�~���O�p�̗v�f�����
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
*	�Đ��J�n(�߂�l�͑���p�̎��ʃL�[)
*******************************************************************************/
string AudioSpeaker::Play(string Name, bool IsLoop, float Volume)
{
	string Key = UniqueNamingSystem::CreateUniqueName<PlayInfo*>(Name, m_PlayInfo);
	PlayInfo* info = SetAudio(Key, Name, IsLoop);

	if (info->AudioInfo->GetIsStreaming())
	{// �X�g���[�~���O�Đ�
		InitBuffer(info);
	}
	else
	{// �ʏ�Đ�
		// �I�[�f�B�I�o�b�t�@�ݒ�
		XAUDIO2_BUFFER bufinfo;
		memset(&bufinfo, 0x00, sizeof(bufinfo));
		bufinfo.AudioBytes = info->AudioInfo->GetAudioBytes();
		bufinfo.pAudioData = info->AudioInfo->GetAudioData();

		// ���[�v�ݒ�
		if (IsLoop)
		{
			bufinfo.LoopBegin = 0;
			bufinfo.LoopLength = info->AudioInfo->GetAudioBytes() / info->AudioInfo->GetWaveFormat()->nBlockAlign;
			bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
		}

		// �o�b�t�@�𔽉f
		info->SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);
	}

	// �Đ��J�n
	info->SourceVoice->SetVolume(info->AudioInfo->GetVolume() * Volume);
	info->SourceVoice->Start();
	info->State = AudioInfo::AudioState::Play;

	return Key;
}

/*******************************************************************************
*	�Đ���~(�L�[�Q��)
*******************************************************************************/
void AudioSpeaker::Stop_FromKey(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// �L�[���L�����m�F
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;

	// �T�E���h���~�����
	info->SourceVoice->Stop();
	info->SourceVoice->DestroyVoice();
	// �X�g���[�~���O�p�̗v�f�����
	if (info->AudioInfo->GetIsStreaming())
	{
		mmioClose(*info->Hmmio, 0);
		delete info->CallBack;
		delete info->PrimaryBuffer;
		delete info->SecondaryBuffer;
	}
	delete info;
	
	// �Đ���񃊃X�g����폜
	m_PlayInfo.erase(Key);
}

/*******************************************************************************
*	�Đ���~(���̎Q�� ����������ꍇ�͌��ݍĐ����̒��ōł��A�Ԃ��������T�E���h)
*******************************************************************************/
void AudioSpeaker::Stop_FromAudioName(string Name)
{
	auto itr = GetIterator_FromAudioName(Name);
	// �����T�E���h���̂̍Đ���񂪑��݂��邩�m�F
	if (itr == m_PlayInfo.end())
	{
		AudioNameUnknownError(Name);
		return;
	}

	PlayInfo* info = itr->second;

	// �T�E���h���~�����
	info->SourceVoice->Stop();
	info->SourceVoice->DestroyVoice();
	// �X�g���[�~���O�p�̗v�f�����
	if (info->AudioInfo->GetIsStreaming())
	{
		mmioClose(*info->Hmmio, 0);
		delete info->CallBack;
		delete info->PrimaryBuffer;
		delete info->SecondaryBuffer;
	}
	delete info;

	// �Đ���񃊃X�g����폜
	m_PlayInfo.erase(itr);
}

/*******************************************************************************
*	�Đ��ĊJ
*******************************************************************************/
void AudioSpeaker::Resume(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// �L�[���L�����m�F
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;
	// �Đ���~���łȂ��ꍇ�͏I��
	if (info->State != AudioInfo::AudioState::Pause) { return; }

	// �Đ��J�n
	info->SourceVoice->SetVolume(info->AudioInfo->GetVolume());
	info->SourceVoice->Start();
	info->State = AudioInfo::AudioState::Play;
}

/*******************************************************************************
*	�ꎞ��~
*******************************************************************************/
void AudioSpeaker::Pause(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// �L�[���L�����m�F
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;
	// �Đ����łȂ��ꍇ�͏I��
	if (info->State != AudioInfo::AudioState::Play) { return; }

	// �Đ���~
	info->SourceVoice->Stop();
	info->State = AudioInfo::AudioState::Pause;
}

/*******************************************************************************
*	�ǉ��̃o�b�t�@��ǂݍ���
*******************************************************************************/
void AudioSpeaker::AddNextBuffer(string Key)
{
	auto itr = m_PlayInfo.find(Key);
	// �L�[���L�����m�F
	if (itr == m_PlayInfo.end())
	{
		KeyUnknownError(Key);
		return;
	}

	PlayInfo* info = itr->second;
	bool endOfSteramFlag = CheckSeek(info);
	// ���[�v�����̐ݒ�Ńf�[�^�̏I�[�ɒB���Ă���ꍇ��
	// �ǉ��̕K�v�͂Ȃ��׏I������
	if (endOfSteramFlag && !info->IsLoop) { return; }

	//------------------------
	// �f�[�^�o�b�t�@����ւ�
	//------------------------
	BYTE* temp = info->PrimaryBuffer;
	LONG primaryBufLength;

	info->PrimaryBuffer = info->SecondaryBuffer;
	info->SecondaryBuffer = temp;
	primaryBufLength = info->SecondaryBufLength;

	//------------------------
	// �f�[�^�o�b�t�@�ǂݍ���
	//------------------------
	info->SecondaryBufLength = mmioRead(*info->Hmmio, (HPSTR)info->SecondaryBuffer, CalcBufferLength(info));
	info->SeekCursor += info->SecondaryBufLength;

	//------------------------
	// �I�[�f�B�I�o�b�t�@�ݒ�
	//------------------------
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = primaryBufLength;
	bufinfo.pAudioData = info->PrimaryBuffer;
	if (endOfSteramFlag)
	{
		// �f�[�^�̏I�[�̏ꍇ�͏I���t���O��n��
		bufinfo.Flags = XAUDIO2_END_OF_STREAM;
	}

	// �o�b�t�@�𔽉f
	info->SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);
}

/*******************************************************************************
*	�T�E���h��o�^
*******************************************************************************/
AudioSpeaker::PlayInfo* AudioSpeaker::SetAudio(string Key, string Name, bool IsLoop)
{
	PlayInfo* info = new PlayInfo();

	info->AudioName = Name;
	info->AudioInfo = AudioContainer::GetAudio_InName(Name);
	info->State = AudioInfo::AudioState::Play;
	info->IsLoop = IsLoop;

	// �X�g���[�~���O�Đ��p
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

	// �T�E���h�\�[�X����
	AudioContainer::GetXaudio()->CreateSourceVoice(
		&info->SourceVoice,
		info->AudioInfo->GetWaveFormat(),
		0,
		XAUDIO2_DEFAULT_FREQ_RATIO,
		info->AudioInfo->GetIsStreaming() ? info->CallBack : NULL);
	assert(info->SourceVoice);

	// �Đ��������X�g�ɒǉ�
	m_PlayInfo[Key] = info;

	return info;
}

/*******************************************************************************
*	�Đ����̃C�e���[�^���擾
* 	(���̎Q�� ����������ꍇ�͌��ݍĐ����̒��ōł��A�Ԃ��������T�E���h)
*******************************************************************************/
map<string, AudioSpeaker::PlayInfo*>::iterator AudioSpeaker::GetIterator_FromAudioName(string Name)
{
	auto itr = m_PlayInfo.begin();

	for (; itr != m_PlayInfo.end() && itr->second->AudioName != Name; itr++);

	return itr;
}

/*******************************************************************************
*	�L���łȂ��L�[���n���ꂽ�ۂ̃G���[����
*******************************************************************************/
void AudioSpeaker::KeyUnknownError(string Key)
{
	string str = string("���݂��Ȃ��L�[�ł̎Q�Ƃ��v������܂����B\n") + Key;
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("audioSpeaker:Error"),
		MB_OK | MB_ICONERROR);
}

/*******************************************************************************
*	�Đ���񃊃X�g�ɑ��݂��Ȃ��T�E���h���̂��n���ꂽ�ۂ̃G���[����
*******************************************************************************/
void AudioSpeaker::AudioNameUnknownError(string Name)
{
	string str = string("�Đ���񃊃X�g�ɑ��݂��Ȃ��T�E���h���̂ł̎Q�Ƃ��v������܂����B\n") + Name;
	MessageBox(GetWindow(),
		TEXT(str.c_str()),
		TEXT("audioSpeaker:Error"),
		MB_OK | MB_ICONERROR);
}

/*******************************************************************************
*	�o�b�t�@�T�C�Y�̕W���l���擾
*******************************************************************************/
LONG AudioSpeaker::GetDefaultBufferLength(PlayInfo* Info)
{
	// 1�b������̃o�C�g���@���@�o�b�t�@������̕b��
	return Info->AudioInfo->GetWaveFormat()->nAvgBytesPerSec * m_SECOND_PER_BUFFER;
}

/*******************************************************************************
*	�X�g���[�~���O�p�o�b�t�@��������
*******************************************************************************/
void AudioSpeaker::InitBuffer(PlayInfo* Info)
{
	//------------------------
	// �f�[�^�o�b�t�@�ǂݍ���
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
	// �I�[�f�B�I�o�b�t�@�ݒ�
	//------------------------
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = primaryBufLength;
	bufinfo.pAudioData = Info->PrimaryBuffer;
	if (endOfSteramFlag)
	{
		// �f�[�^�̏I�[�̏ꍇ�͏I���t���O��n��
		bufinfo.Flags = XAUDIO2_END_OF_STREAM;
	}

	// �o�b�t�@�𔽉f
	Info->SourceVoice->SubmitSourceBuffer(&bufinfo, NULL);
}

/*******************************************************************************
*	�m�ۉ\�ȃo�b�t�@�T�C�Y���v�Z
*******************************************************************************/
LONG AudioSpeaker::CalcBufferLength(PlayInfo* Info)
{
	LONG defaultLen = GetDefaultBufferLength(Info);
	LONG audioBytes = Info->AudioInfo->GetAudioBytes();

	// �c��̃T�E���h�f�[�^�ʂ��o�b�t�@�T�C�Y�̕����傫�����ǂ���
	if (audioBytes - Info->SeekCursor < defaultLen)
	{// �傫���ꍇ
		// �c��̃T�E���h�f�[�^�ʂ�Ԃ�
		return audioBytes - Info->SeekCursor;
	}
	else
	{// �傫���Ȃ��ꍇ
		// �o�b�t�@�T�C�Y��Ԃ�
		return defaultLen;
	}
}

/*******************************************************************************
*	�V�[�N�ʒu���I�[�ɒB���Ă��邩�m�F����
*******************************************************************************/
bool AudioSpeaker::CheckSeek(PlayInfo* Info)
{
	LONG audioBytes = Info->AudioInfo->GetAudioBytes();

	// �f�[�^�̏I�[�܂œǂݍ��݂��I�����Ă��邩�ǂ���
	if (Info->SeekCursor >= audioBytes)
	{
		if (Info->IsLoop)
		{
			// �Ō�܂œǂݍ��ݍς݂̏ꍇ�̓V�[�N��擪�ɖ߂����[�v�ɔ�����
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


//�@�����@�R�[���o�b�N�N���X�̃��\�b�h�@����

/*******************************************************************************
*	XAUDIO2_END_OF_STREAM�t���O�𗧂Ă���Ԃ�
* 	���݂̃o�b�t�@�̍Ō�̃o�C�g������ꂽ����ɌĂяo�����
*******************************************************************************/
void AudioCallback::OnStreamEnd()
{
	// ���[�v�ݒ�ł͂Ȃ��ꍇ��~����
	if (!m_AudioSpeaker->GetPlayInfo_FromKey(m_Key)->IsLoop)
	{
		m_AudioSpeaker->Stop_FromKey(m_Key);
	}
}

/*******************************************************************************
*	���݂̃o�b�t�@�̍Ō�̃o�C�g������ꂽ����ɌĂяo�����
*******************************************************************************/
void AudioCallback::OnBufferEnd(void* pBufferContext)
{
	m_AudioSpeaker->AddNextBuffer(m_Key);
}
