/*******************************************************************************
*
*	�^�C�g���F	�Q�[���S�̊Ǘ��p�ÓI�N���X	[ manager.cpp ]
*
*	�쐬�ҁF	�Ö{ �ח�
*
*******************************************************************************/
#include "manager.h"

// �ÓI�N���X
#include "renderer.h"
#include "time.h"
#include "input.h"
#include "modelContainer.h"
#include "textureContainer.h"
#include "audioContainer.h"
#include "skyDome.h"
#include "savedataManager.h"
#include "collision3dManager.h"
#include "collider3d.h"
#include "debugManager.h"
#ifdef _DEBUG
#include "debugConsole.h"
#endif

// ��ԍŏ��ɊJ�n����V�[��
#include "test.h"
#include "demo_Invoke.h"
#include "demo_Parent.h"
#include "demo_CollisionSplit0.h"

#include <typeinfo>

void Manager::Init(HINSTANCE hInstance)
{
	// �ÓI�N���X�̏�����
#ifdef _DEBUG
	DebugConsole::Init();
#endif
	Renderer::Init();
	Input::Init(hInstance);
	TextureContainer::Init();
	ModelContainer::Init();
	AudioContainer::Init();
	SkyDome::Init();
	Transition::Init();
	SavedataManager::Init();
	Collision3DManager::Init(3, D3DXVECTOR3(-50.0f, -50.0f, -50.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));

#ifdef _DEBUG
	DebugManager::Init();
#endif

	// �ŏ��̃V�[�����N��
	SetScene<Demo_Parent>(Transition::GetFirstTransitionOption());
	CheckScene();

	// ���[�h���Ԃ��v�����Ԃɓ���Ă��܂��̂ōŌ�ɍs��
	Time::Init();
}

void Manager::Uninit()
{
	// �������Ƌt���ɏI���������s��
	m_Scene->Uninit();
	delete m_Scene;

	Collision3DManager::Uninit();
	SavedataManager::Uninit();
	Transition::Uninit();
	SkyDome::Uninit();
	AudioContainer::Uninit();
	ModelContainer::Uninit();
	TextureContainer::Uninit();
	Input::Uninit();
	Time::Uninit();
	Renderer::Uninit();
#ifdef _DEBUG
	DebugConsole::Uninit();
	DebugManager::Uninit();
#endif
}

void Manager::Update()
{
	// �ÓI�N���X�X�V
#ifdef _DEBUG
	DebugConsole::Update();
#endif
	Time::Update();
	Input::Update();

	// �V�[���X�V
	m_Scene->Update();

	// �I�u�W�F�N�g�̍X�V��ɏՓ˔�����s��
	Collision3DManager::Update();

	// �`��̃^�C�~���O�ɍ��킹�ăV�[���̌�ɍs��
	Transition::Update();

	// �I�u�W�F�N�g�̍폜���m�F����
	m_Scene->CheckObjectDestroy();

#ifdef _DEBUG
	// �f�o�b�O����\��
	DebugManager::Update();
#endif

	// �V�[���J�ڂ��s�����m�F
	CheckScene();
}

void Manager::Draw()
{
	// �w�i���N���A����
	Renderer::Begin();

	Collision3DManager::Draw();

	// �V�[�����I�u�W�F�N�g�`��
	m_Scene->Draw();

	// �g�����W�V��������Ԏ�O�łȂ���΂Ȃ�Ȃ����߂��̃^�C�~���O
	Transition::Draw();

#ifdef _DEBUG
	DebugManager::Draw();
#endif

	// ��ʂ��X���b�v
	Renderer::End();
}

/*******************************************************************************
*	�V�[���J�ڂ��s�����m�F
*******************************************************************************/
void Manager::CheckScene()
{
	// �\�񂪖����ꍇ�܂��̓g�����W�V�������̏ꍇ�͑J�ڂ����I������
	if (!m_NextScene ||
		Transition::GetTransitionState() == Transition::TransitionState::Out)
	{ return; }

	//------------------------
	// �J�ڏ���
	//------------------------
	if (m_Scene)
	{
		// ���݂܂ł̃V�[�����폜
		m_Scene->Uninit();
		delete m_Scene;
	}

	// �\�񂵂��V�[���ɐ؂�ւ�
	m_Scene = m_NextScene;
	m_NextScene = nullptr;

	// ������
	m_Scene->Init();
	Transition::StartTransitionIn();
}
