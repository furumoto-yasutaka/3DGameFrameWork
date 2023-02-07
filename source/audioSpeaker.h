/*******************************************************************************
*
*	�^�C�g���F	�T�E���h�Đ��p�R���|�[�l���g	[ audioSpeaker.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
	// �Đ��p�̏����܂Ƃ߂��\����
	struct PlayInfo
	{
		string					AudioName;			// �T�E���h�̖���(�R���e�i��̖��O)
		AudioInfo*				AudioInfo;			// �T�E���h�̏ڍ׏��
		AudioInfo::AudioState	State;				// �T�E���h�̏��
		bool					IsLoop;				// ���[�v�̗L��
		IXAudio2SourceVoice*	SourceVoice;		// �X�s�[�J�[

		// �X�g���[�~���O�Đ����̂ݎg�p
		HMMIO*					Hmmio;				// �ǂݍ��ݗp�n���h��
		AudioCallback*			CallBack;			// �R�[���o�b�N�N���X
		BYTE*					PrimaryBuffer;		// �o�b�t�@1
		BYTE*					SecondaryBuffer;	// �o�b�t�@2
		LONG					SecondaryBufLength;	// �o�b�t�@2�̂����g�p���Ă���̈�
		LONG					SeekCursor;			// �t�@�C���̓ǂݍ��݈ʒu
	};

private:
	static inline list<AudioSpeaker*>	m_SpeakerList;				// �T�E���h�̑S�̑���p�C���X�^���X���X�g
	static inline const unsigned int	m_SECOND_PER_BUFFER = 1;	// �X�g���[�~���O�Đ��p�̃o�b�t�@�T�C�Y���T�E���h�̉��b�m�ۂ��邩

	// ���v�f
	// ����1	string�^	���ʃL�[(�T�E���h����(�A��))
	// ����2	PlayInfo*�^	�Đ����
	map<string, PlayInfo*>	m_PlayInfo;		// �Đ���񃊃X�g

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

	// �Đ��J�n(�߂�l�͑���p�̎��ʃL�[)
	string Play(string Name, bool IsLoop = false, float Volume = 1.0f);

	// �Đ���~(�L�[�Q��)
	void Stop_FromKey(string Key);

	// �Đ���~(���̎Q�� ����������ꍇ�͌��ݍĐ����̒��ōł��A�Ԃ��������T�E���h)
	void Stop_FromAudioName(string Name);

	// �Đ��ĊJ
	void Resume(string Key);

	// �ꎞ��~
	void Pause(string Key);

	/////////////////////////////////////////////////
	//�@�����@�X�g���[�~���O�Đ��p���\�b�h�@�����@//

	// �ǉ��̃o�b�t�@��ǂݍ���
	void AddNextBuffer(string Key);

	// �Đ������擾(�L�[�Q��)
	PlayInfo* GetPlayInfo_FromKey(string Key) { return m_PlayInfo[Key]; }

	/////////////////////////////////////////////////
private:
	// �T�E���h��o�^
	PlayInfo* SetAudio(string Key, string Name, bool IsLoop);

	// �Đ����̃C�e���[�^���擾
	// (���̎Q�� ����������ꍇ�͌��ݍĐ����̒��ōł��A�Ԃ��������T�E���h)
	map<string, PlayInfo*>::iterator GetIterator_FromAudioName(string Name);
	
	// �L���łȂ��L�[���n���ꂽ�ۂ̃G���[����
	void KeyUnknownError(string Key);

	// �Đ���񃊃X�g�ɑ��݂��Ȃ��T�E���h���̂��n���ꂽ�ۂ̃G���[����
	void AudioNameUnknownError(string Name);

	/////////////////////////////////////////////////
	//�@�����@�X�g���[�~���O�Đ��p���\�b�h�@�����@//
	
	// �o�b�t�@�T�C�Y�̕W���l���擾
	LONG GetDefaultBufferLength(PlayInfo* Info);

	// �X�g���[�~���O�p�o�b�t�@��������
	void InitBuffer(PlayInfo* Info);

	// �m�ۉ\�ȃo�b�t�@�T�C�Y���v�Z
	LONG CalcBufferLength(PlayInfo* Info);

	// �V�[�N�ʒu���I�[�ɒB���Ă��邩�m�F����
	bool CheckSeek(PlayInfo* Info);
	/////////////////////////////////////////////////
};

//--------------------------------------------
// �X�g���[�~���O�Đ��p�R�[���o�b�N�N���X
//--------------------------------------------
class AudioCallback : public IXAudio2VoiceCallback
{
private:
	AudioSpeaker*	m_AudioSpeaker;	// �X�s�[�J�[
	string			m_Key;			// �X�s�[�J�[�ɓo�^���ꂽ�T�E���h�̎��ʃL�[

public:
	AudioCallback(AudioSpeaker* AudioSpeaker, string Key)
		: m_AudioSpeaker(AudioSpeaker), m_Key(Key) {}
	// ????
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired) {}
	// ????
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(void) {}
	// XAUDIO2_END_OF_STREAM�t���O�𗧂Ă���Ԃ�
	// ���݂̃o�b�t�@�̍Ō�̃o�C�g������ꂽ����ɌĂяo�����
	void STDMETHODCALLTYPE OnStreamEnd(void);
	// ���݂̃o�b�t�@�̍ŏ��̃o�C�g�������钼�O�ɌĂяo�����
	void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) {}
	// ���݂̃o�b�t�@�̍Ō�̃o�C�g������ꂽ����ɌĂяo�����
	void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext);
	// ���[�v�̏I���n�_�ɒB�����Ƃ��ɌĂяo�����
	void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) {}
	// �T�E���h�ɉ��炩�̃G���[�������������ɌĂяo�����(�H)
	void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) {}
};
