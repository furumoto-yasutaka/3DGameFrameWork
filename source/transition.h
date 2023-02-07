/*******************************************************************************
*
*	�^�C�g���F	�J�ډ��o�p�ÓI�N���X	[ transition.h ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#pragma once
#include "main.h"
#include "renderer.h"
#include "textureContainer.h"
#include "callbackListner.h"

#include <functional>

class Texture;
class Component;

class Transition
{
public:
	// �g�����W�V�����̌`��
	enum class TransitionPattern
	{
		None = 0,	// �ς��Ɛ؂�ւ�
		Fade,		// �t�F�[�h
		Wipe,
	};
	// �g�����W�V�����̏�
	enum class TransitionState
	{
		Out = 0,		// ��ʂ��B���Ă���
		In,				// ��ʂ������Ă���
		OutComplete,	// ��ʂ��B�ꂽ��ԂɂȂ���
		None,			// �������E��ʂ��������ԂɂȂ���
		Length,
	};

	// �g�����W�V�����ݒ�p�\����
	struct TransitionOption
	{
		Transition::TransitionPattern	Mode[2];			// ���݂͖��g�p
		float							TimeLimitSec[2];
		Texture*						Texture;

		TransitionOption()
		{
			for (int i = 0; i < 2; i++)
			{
				Mode[i] = TransitionPattern::None;
				TimeLimitSec[i] = 0.0f;
			}
			Texture = NULL;
		}
	};

private:
	static inline TransitionState		m_State;				// �g�����W�V�����̏�
	static inline TransitionOption		m_Option;				// �g�����W�V�����ݒ�
	static inline float					m_TimeCountSec = 0.0f;	// �o�ߎ���
	static inline bool					m_IsLoadFrame = false;	// ���[�h������t���[��

	static inline ID3D11Buffer*			m_VertexBuffer = NULL;	// ���_�o�b�t�@
	static inline ID3D11VertexShader*	m_VertexShader = NULL;	// ���_�V�F�[�_�[
	static inline ID3D11PixelShader*	m_PixelShader = NULL;	// �s�N�Z���V�F�[�_�[
	static inline ID3D11InputLayout*	m_VertexLayout = NULL;	// ���̓��C�A�E�g

	static inline CallBackBase*			m_CallBack = NULL;		// �R�[���o�b�N�֐�(�V�[�����؂�ւ�����u�ԌĂ΂��)

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �V�[���؂�ւ��O�g�����W�V�����J�n
	static void StartTransitionOut(TransitionOption Option);

	// �V�[���؂�ւ���g�����W�V�����J�n
	static void StartTransitionIn();

	// �Q�[���N�����̃g�����W�V�����I�v�V�������擾
	static TransitionOption GetFirstTransitionOption();

	/////////////////////////////
	//�@�����@�A�N�Z�T�@�����@//
	static void SetTransitionOption(TransitionOption Option) { m_Option = Option; }

	static TransitionState GetTransitionState() { return m_State; }

	// �R�[���o�b�N��ݒ�
	template<class T>
	static void SetCallBack(T* Origin, void(T::* Function)())
	{
		m_CallBack = new CallBackListner<T>(Origin, Function);
	}
	/////////////////////////////
private:
	// ���_���𐶐�
	static void CreateVertex(VERTEX_3D* Vertex, float Alpha);
	static void CreateVertex_WipeLeft(VERTEX_3D* Vertex, float Rate);
	static void CreateVertex_WipeRight(VERTEX_3D* Vertex, float Rate);

	// �`�揈��
	static void Draw_Fade();
	static void Draw_Wipe();
};
