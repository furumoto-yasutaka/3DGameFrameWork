/*******************************************************************************
*
*	タイトル：	パーティクル生成通知クラス	[ particleEmitChecker.h ]
*
*	作成者：	古本 泰隆
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
	float m_CreateInterval = 0.0f;	// 生成のインターバル
	float m_NextBorder = 0.0f;		// 生成までの経過時間

public:
	ParticleEmitChacker_RateOverTime(float CreateInterval)
		: m_CreateInterval(CreateInterval),
		m_NextBorder(CreateInterval)
	{
		assert(m_CreateInterval > 0.0f);
	}

	void CheckGenerate(float ElapsedTime) override
	{
		// 生成までの経過時間を過ぎたらパーティクルを生成
		while (ElapsedTime >= m_NextBorder)
		{
			m_NextBorder += m_CreateInterval;
			
			// ↓コンピュートシェーダーでパーティクル生成↓
			m_ParticleSystem->RunConputeShader_Emit(1);
		}
	}
};

class ParticleEmitChacker_Burst : public ParticleEmitChackerBase
{
private:
	float m_CreateStartTime = 0.0f;	// 生成開始待機時間
	int m_CreateParticles = 0;		// 生成1回あたりのパーティクル数
	int m_CreateCycles = 0;			// 生成回数
	int m_CreateCyclesCount = 0;	// 残り生成回数
	float m_CreateInterval = 0.0f;	// 生成のインターバル
	float m_NextBorder = 0.0f;		// 生成までの経過時間
	float m_Probability = 1.0f;		// 生成が発生する確率

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
		// 生成開始待機時間と生成までの経過時間を過ぎたらパーティクルを生成
		if (ElapsedTime > m_CreateStartTime && ElapsedTime > m_NextBorder)
		{
			// 生成回数がまだ残っているかつ指定した確率でパーティクルを生成
			if (m_CreateCyclesCount > 0 && m_Probability >= Math::Random(1.0f))
			{
				m_NextBorder += m_CreateInterval;
				m_CreateCyclesCount--;

				// ↓コンピュートシェーダーでパーティクル生成↓
				m_ParticleSystem->RunConputeShader_Emit(m_CreateParticles);
			}
		}
	}
};
