#include "SceneManager.h"
#include "Sound/SoundManager.h"

SceneManager::SceneManager()
	: m_pScene	( nullptr )
	, m_hWnd	()
	, m_pDx11	()
	, m_pDx9	()
{

}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	LoadScene(List::Main);
	return S_OK;
}

void SceneManager::Update()
{
	m_pScene->Update();
}

void SceneManager::Draw()
{
	m_pScene->Draw();
}

void SceneManager::LoadScene(List Scene)
{
	m_pScene.reset();

	//�V�[���쐬.
	MakeScene(Scene);
	m_pScene->Create();
}

HWND SceneManager::GetHWND() const
{
	return m_hWnd;
}

//�V�[���쐬.
void SceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
	//case SceneManager::Title:
	//	m_pScene = std::make_unique<Title>();
	//	//BGM���~�߂�.
	//	SoundManager::Stop(SoundManager::BGM_Over);
	//	SoundManager::Stop(SoundManager::BGM_Ending);
	//	//BGM�̃��[�v�Đ�.
	//	SoundManager::PlayLoop(SoundManager::BGM_Title);
	//	break;
	case SceneManager::Main:
		m_pScene = std::make_unique<GameMain>();
		//SE���~�߂�.
		//BGM���~�߂�.
		SoundManager::Stop(SoundManager::BGM_Title);
		//BGM�̃��[�v�Đ�.
		SoundManager::PlayLoop(SoundManager::BGM_Main);
		break;
	//case SceneManager::GameOver:
	//	m_pScene = std::make_unique<GameOver>();
	//	//BGM���~�߂�.
	//	SoundManager::Stop(SoundManager::BGM_Main);
	//	//BGM���[�v.
	//	SoundManager::PlayLoop(SoundManager::BGM_Over);
	//	break;
	//case SceneManager::Ending:
	//	m_pScene = std::make_unique<Ending>();
	//	//BGM���~�߂�.
	//	SoundManager::Stop(SoundManager::BGM_Main);
	//	//BGM���[�v.
	//	SoundManager::PlayLoop(SoundManager::BGM_Ending);
	//	break;
	default:
		break;
	}
}
