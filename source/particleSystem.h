/*******************************************************************************
*
*	�^�C�g���F	�p�[�e�B�N�������Ǘ��R���|�[�l���g	[ particleSystem.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
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
		World = 0,	// ���[���h�}�g���N�X���f�t�H���g�ɐݒ肵�ăp�[�e�B�N���̃p�����[�^�ɑ������
		Local,		// ���[���h�}�g���N�X�������ʂ�ݒ肷��
	};
	enum class EmitterStopActionId
	{
		ComponentDisable = 0,
		ObjectDestroy,
		ComponentDestroy,
	};
	enum class ParticleDirectionModeId
	{
		BillboardDirection = 0,	// �J�����̕����Ɍ�����
		RandomizeDirection,		// �p�[�e�B�N���������_���ȕ����Ɍ�����
		AlignToDirection,		// �ŏ��ɐݒ肵�����������ɉ�]���ăJ�����֌�����
	};

	struct EmitParam
	{
		bool					IsLooping;			// ���[�v�t���O
		float					Duration;			// �G�~�b�^�[��1�T�C�N���̎���
		float					DurationCount;		// �G�~�b�^�[�̃T�C�N���̃J�E���g
		unsigned int			MaxParticles;		// �����ɑ��݉\�ȍő�p�[�e�B�N�������w�肷��
		unsigned int			ParticleCount;		// ���ݑ��݂���p�[�e�B�N����
		D3DXVECTOR3				Offset;				// �G�~�b�^�[�̍��W����(�p�[�e�B�N���������Ƀp�[�e�B�N���̍��W�ɑ������킹��)
		SimulationSpaceId		SimulationSpace;	// �G�~�b�^�[�̍��W�
		EmitterStopActionId		StopAction;			// �G�t�F�N�g�I�����̋���
		CallBackBase*			StopCallback;		// �R�[���o�b�N�֐�

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
		bool			IsActive;	// �g�p�����ǂ���
		float			Lifetime;	// �p�[�e�B�N������������ł܂ł̎���
		D3DXVECTOR2		Size;		// �p�[�e�B�N���̃T�C�Y
		D3DXVECTOR3		Position;	// �p�[�e�B�N���̍��W
		D3DXVECTOR3		Velocity;	// �p�[�e�B�N���̏���
		D3DXVECTOR3		Gravity;	// �p�[�e�B�N���ɂ�����d��
		D3DXVECTOR4		Color;		// �p�[�e�B�N���̐F
	};

	struct ParticleDefaultParam
	{
		float						Lifetime;				// �p�[�e�B�N������������ł܂ł̎���
		Math::MinMax<D3DXVECTOR2>	StartSize;				// �p�[�e�B�N���̃T�C�Y
		D3DXVECTOR3					Position;				// �p�[�e�B�N���̏������W(�Q�[���I�u�W�F�N�g�̍��W�ƃI�t�Z�b�g�𑫂������́����t���[���X�V�̕K�v����)
		Math::MinMax<D3DXVECTOR3>	StartVelocity;			// �p�[�e�B�N���̏���
		D3DXVECTOR3					Gravity;				// �p�[�e�B�N���ɂ�����d��
		string						TexName;				// �e�N�X�`����
		Texture*					Tex;					// �p�[�e�B�N���̃e�N�X�`��
		D3DXVECTOR4					Color;					// �p�[�e�B�N���̐F

		ParticleDefaultParam();
		ParticleDefaultParam(float Lifetime, Math::MinMax<D3DXVECTOR2> StartSize,
			Math::MinMax<D3DXVECTOR3> StartVelocity,
			D3DXVECTOR3 Gravity, string TexName, D3DXVECTOR4 Color);
	};

	struct ParticleDefaultParamSRV
	{
		float						Lifetime;				// �p�[�e�B�N������������ł܂ł̎���
		D3DXVECTOR2					StartSizeMax;			// �p�[�e�B�N���̃T�C�Y
		D3DXVECTOR2					StartSizeMin;			// �p�[�e�B�N���̃T�C�Y
		D3DXVECTOR3					Position;				// �p�[�e�B�N���̏������W(�Q�[���I�u�W�F�N�g�̍��W�ƃI�t�Z�b�g�𑫂������́����t���[���X�V�̕K�v����)
		D3DXVECTOR3					StartVelocityMax;		// �p�[�e�B�N���̏���
		D3DXVECTOR3					StartVelocityMin;		// �p�[�e�B�N���̏���
		D3DXVECTOR3					Gravity;				// �p�[�e�B�N���ɂ�����d��
		D3DXVECTOR4					Color;					// �p�[�e�B�N���̐F
	};

private:

	bool						m_IsPlay = false;
	EmitParam					m_EmitterParam;				// �G�~�b�^�[�̃p�����[�^
	ParticleDefaultParam		m_ParticleDefaultParam;		// �p�[�e�B�N���̃f�t�H���g�p�����[�^
	ParticleEmitChackerBase*	m_EmitChacker = NULL;		// �p�[�e�B�N�������ʒm�N���X
	
	ID3D11ComputeShader*		m_ComputeShader_SetList = NULL;
	ID3D11ComputeShader*		m_ComputeShader_Init = NULL;
	ID3D11ComputeShader*		m_ComputeShader_Emit = NULL;
	ID3D11ComputeShader*		m_ComputeShader_Update = NULL;

	// �R���s���[�g�V�F�[�_�[���\�[�X
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


	// �`��p���\�[�X
	ID3D11Buffer*				m_VertexBuffer = NULL;		// ���_�o�b�t�@
	ID3D11VertexShader*			m_VertexShader = NULL;		// ���_�V�F�[�_�[
	ID3D11PixelShader*			m_PixelShader = NULL;		// �s�N�Z���V�F�[�_�[
	ID3D11InputLayout*			m_VertexLayout = NULL;		// ���̓��C�A�E�g

	list<CallBackInvokeBase*>	m_InvokeList;				// �w�莞�ԑ҂��R�[���o�b�N���X�g

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
