/*******************************************************************************
*
*	タイトル：	パーティクル生成管理コンポーネント	[ particleSystem.h ]
*
*	作成者：	古本 泰隆
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "draw3dComponent.h"
#include "callbackListner.h"

#include <string>
#include <list>
#include <string>

class Texture;
class CallBackBase;
class ParticleEmitChackerBase;

class ParticleSystem : public Draw3DComponent
{
public:
	enum class SimulationSpaceId
	{
		World = 0,	// ワールドマトリクスをデフォルトに設定してパーティクルのパラメータに代入する
		Local,		// ワールドマトリクスをいつも通り設定する
	};
	enum class EmitterStopActionId
	{
		ComponentDisable = 0,
		ObjectDestroy,
		ComponentDestroy,
	};
	enum class ParticleDirectionModeId
	{
		BillboardDirection = 0,	// カメラの方向に向ける
		RandomizeDirection,		// パーティクルをランダムな方向に向ける
		AlignToDirection,		// 最初に設定した方向を軸に回転してカメラへ向ける
	};

	struct EmitParam
	{
		bool					IsLooping;			// ループフラグ
		float					Duration;			// エミッターの1サイクルの時間
		float					DurationCount;		// エミッターのサイクルのカウント
		unsigned int			MaxParticles;		// 同時に存在可能な最大パーティクル数を指定する
		unsigned int			ParticleCount;		// 現在存在するパーティクル数
		D3DXVECTOR3				Offset;				// エミッターの座標差異(パーティクル生成時にパーティクルの座標に足し合わせる)
		SimulationSpaceId		SimulationSpace;	// エミッターの座標基準
		EmitterStopActionId		StopAction;			// エフェクト終了時の挙動
		CallBackBase*			StopCallback;		// コールバック関数

		EmitParam();
		EmitParam(bool IsLooping, float Duration, int MaxParticles,
			D3DXVECTOR3 Offset, D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale,
			SimulationSpaceId SimulationSpace, EmitterStopActionId StopAction)
		{
			this->IsLooping = IsLooping;
			this->Duration = Duration;
			this->DurationCount = Duration;
			this->MaxParticles = MaxParticles;
			this->ParticleCount = 0;
			this->Offset = Offset;
			this->SimulationSpace = SimulationSpace;
			this->StopAction = StopAction;
			this->StopCallback = NULL;
		}
		template<class T>
		EmitParam(bool IsLooping, float Duration, int MaxParticles, D3DXVECTOR3 Offset,
			D3DXVECTOR3 Rotation, D3DXVECTOR3 Scale, SimulationSpaceId SimulationSpace,
			EmitterStopActionId StopAction, T* CallbackOrigin, void(T::* CallBackFunction)())
		{
			this->IsLooping = IsLooping;
			this->Duration = Duration;
			this->DurationCount = Duration;
			this->MaxParticles = MaxParticles;
			this->ParticleCount = 0;
			this->Offset = Offset;
			this->SimulationSpace = SimulationSpace;
			this->StopAction = StopAction;
			if (CallbackOrigin && CallBackFunction)
			{
				this->StopCallback = new CallBackListner<T>(CallbackOrigin, CallBackFunction);
			}
			else
			{
				this->StopCallback = NULL;
			}
		}
	};

	struct ParticleParam
	{
		bool			IsActive;	// 使用中かどうか
		float			Lifetime;	// パーティクル発生から消滅までの時間
		D3DXVECTOR2		Size;		// パーティクルのサイズ
		D3DXVECTOR3		Position;	// パーティクルの座標
		D3DXVECTOR3		Velocity;	// パーティクルの初速
		D3DXVECTOR3		Gravity;	// パーティクルにかかる重力
		D3DXVECTOR4		Color;		// パーティクルの色
	};

	struct ParticleDefaultParam
	{
		float						Lifetime;				// パーティクル発生から消滅までの時間
		Math::MinMax<D3DXVECTOR2>	StartSize;				// パーティクルのサイズ
		D3DXVECTOR3					Position;				// パーティクルの初期座標(ゲームオブジェクトの座標とオフセットを足したもの※毎フレーム更新の必要あり)
		Math::MinMax<D3DXVECTOR3>	StartVelocity;			// パーティクルの初速
		D3DXVECTOR3					Gravity;				// パーティクルにかかる重力
		string						TexName;				// テクスチャ名
		Texture*					Tex;					// パーティクルのテクスチャ
		D3DXVECTOR4					Color;					// パーティクルの色

		ParticleDefaultParam();
		ParticleDefaultParam(float Lifetime, Math::MinMax<D3DXVECTOR2> StartSize,
			Math::MinMax<D3DXVECTOR3> StartVelocity,
			D3DXVECTOR3 Gravity, string TexName, D3DXVECTOR4 Color);
	};

	struct ParticleDefaultParamSRV
	{
		float						Lifetime;				// パーティクル発生から消滅までの時間
		D3DXVECTOR2					StartSizeMax;			// パーティクルのサイズ
		D3DXVECTOR2					StartSizeMin;			// パーティクルのサイズ
		D3DXVECTOR3					Position;				// パーティクルの初期座標(ゲームオブジェクトの座標とオフセットを足したもの※毎フレーム更新の必要あり)
		D3DXVECTOR3					StartVelocityMax;		// パーティクルの初速
		D3DXVECTOR3					StartVelocityMin;		// パーティクルの初速
		D3DXVECTOR3					Gravity;				// パーティクルにかかる重力
		D3DXVECTOR4					Color;					// パーティクルの色
	};

private:

	bool						m_IsPlay = false;
	EmitParam					m_EmitterParam;				// エミッターのパラメータ
	ParticleDefaultParam		m_ParticleDefaultParam;		// パーティクルのデフォルトパラメータ
	ParticleEmitChackerBase*	m_EmitChacker = NULL;		// パーティクル生成通知クラス
	
	ID3D11ComputeShader*		m_ComputeShader_SetList = NULL;
	ID3D11ComputeShader*		m_ComputeShader_Init = NULL;
	ID3D11ComputeShader*		m_ComputeShader_Emit = NULL;
	ID3D11ComputeShader*		m_ComputeShader_Update = NULL;

	// コンピュートシェーダーリソース
	ID3D11Buffer*				m_ParticleParamBuf = NULL;
	ID3D11ShaderResourceView*	m_ParticleParamSRV = NULL;
	ID3D11UnorderedAccessView*	m_ParticleParamUAV = NULL;

	ID3D11Buffer*				m_ParticlePoolBuf = NULL;
	ID3D11UnorderedAccessView*	m_ParticlePoolUAV = NULL;

	ID3D11Buffer*				m_ParticlePoolCountBuf = NULL;
	ID3D11UnorderedAccessView*	m_ParticlePoolCountUAV = NULL;

	ID3D11Buffer*				m_ParticleDefaultParamBuf = NULL;
	ID3D11ShaderResourceView*	m_ParticleDefaultParamSRV = NULL;

	ID3D11Buffer*				m_DeltaTimeBuf = NULL;
	ID3D11ShaderResourceView*	m_DeltaTimeSRV = NULL;


	// 描画用リソース
	ID3D11Buffer*				m_VertexBuffer = NULL;		// 頂点バッファ
	ID3D11VertexShader*			m_VertexShader = NULL;		// 頂点シェーダー
	ID3D11PixelShader*			m_PixelShader = NULL;		// ピクセルシェーダー
	ID3D11InputLayout*			m_VertexLayout = NULL;		// 入力レイアウト

	list<CallBackInvokeBase*>	m_InvokeList;				// 指定時間待ちコールバックリスト

public:
	ParticleSystem(GameObject* AttachObject) : Draw3DComponent(AttachObject) {}

	void Init(float GenerateDelay, bool IsPlayOnAwake,
		ParticleSystem::EmitParam EmitterParam,
		ParticleDefaultParam ParticleDefaltParam,
		ParticleEmitChackerBase* ParticleEmitChacker);
	void Uninit() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;

	void Play();
	void Pause();
	void Stop();

	void RunConputeShader_Emit(int Count);

private:
	void CreateShader();
	void CreateVertex();
	void CreateBuffer();
	ID3D11ShaderResourceView* CreateSRV(ID3D11Buffer* Buf, int NumElements);
	ID3D11UnorderedAccessView* CreateUAV(ID3D11Buffer* Buf, int NumElements);

	void RunConputeShader_SetList();
	void RunConputeShader_Init();
	void RunConputeShader_Update();

	void CheckEmitStop();
	void EndSystem();

	void CheckInvoke();
	template<class T>
	void SetInvoke(T* Origin, void(T::* Function)(), float Time)
	{
		m_InvokeList.push_back(new CallBackInvoke<T>(this, Function, Time));
	}

	ID3D11Buffer* CreateAndCopyToDebugBuf(ID3D11Buffer* pBuffer);
};
