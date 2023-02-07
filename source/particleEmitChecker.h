/*******************************************************************************
*
*	�^�C�g���F	�p�[�e�B�N�������ʒm�N���X	[ particleEmitChecker.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "particleSystem.h"

class ParticleEmitChackerBase
{
protected:
	ParticleSystem* m_ParticleSystem = NULL;

public:
	virtual void CheckGenerate(float ElapsedTime) = 0;
	void SetParticleSystem(ParticleSystem* System) { m_ParticleSystem = System; }
};

class ParticleEmitChacker_RateOverTime : public ParticleEmitChackerBase
{
private:
	float m_CreateInterval = 0.0f;	// �����̃C���^�[�o��
	float m_NextBorder = 0.0f;		// �����܂ł̌o�ߎ���

public:
	ParticleEmitChacker_RateOverTime(float CreateInterval)
		: m_CreateInterval(CreateInterval),
		m_NextBorder(CreateInterval)
	{
		assert(m_CreateInterval > 0.0f);
	}

	void CheckGenerate(float ElapsedTime) override
	{
		// �����܂ł̌o�ߎ��Ԃ��߂�����p�[�e�B�N���𐶐�
		while (ElapsedTime >= m_NextBorder)
		{
			m_NextBorder += m_CreateInterval;
			
			// ���R���s���[�g�V�F�[�_�[�Ńp�[�e�B�N��������
			m_ParticleSystem->RunConputeShader_Emit(1);
		}
	}
};

class ParticleEmitChacker_Burst : public ParticleEmitChackerBase
{
private:
	float m_CreateStartTime = 0.0f;	// �����J�n�ҋ@����
	int m_CreateParticles = 0;		// ����1�񂠂���̃p�[�e�B�N����
	int m_CreateCycles = 0;			// ������
	int m_CreateCyclesCount = 0;	// �c�萶����
	float m_CreateInterval = 0.0f;	// �����̃C���^�[�o��
	float m_NextBorder = 0.0f;		// �����܂ł̌o�ߎ���
	float m_Probability = 1.0f;		// ��������������m��

public:
	ParticleEmitChacker_Burst(
		float CreateStartTime, int CreateParticles,
		int CreateCycles, float CreateInterval, float Probability)
		: m_CreateStartTime(CreateStartTime),
		m_CreateParticles(CreateParticles),
		m_CreateCycles(CreateCycles),
		m_CreateCyclesCount(CreateCycles),
		m_CreateInterval(CreateInterval),
		m_NextBorder(CreateStartTime),
		m_Probability(Probability)
	{
		assert(m_CreateStartTime >= 0.0f);
		assert(m_CreateCycles >= 0);
		assert(m_CreateInterval > 0.0f);
		assert(m_Probability >= 0.0f);
	}

	void CheckGenerate(float ElapsedTime) override
	{
		// �����J�n�ҋ@���ԂƐ����܂ł̌o�ߎ��Ԃ��߂�����p�[�e�B�N���𐶐�
		if (ElapsedTime > m_CreateStartTime && ElapsedTime > m_NextBorder)
		{
			// �����񐔂��܂��c���Ă��邩�w�肵���m���Ńp�[�e�B�N���𐶐�
			if (m_CreateCyclesCount > 0 && m_Probability >= Math::Random(1.0f))
			{
				m_NextBorder += m_CreateInterval;
				m_CreateCyclesCount--;

				// ���R���s���[�g�V�F�[�_�[�Ńp�[�e�B�N��������
				m_ParticleSystem->RunConputeShader_Emit(m_CreateParticles);
			}
		}
	}
};
