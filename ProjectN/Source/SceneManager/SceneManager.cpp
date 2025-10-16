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

	//シーン作成.
	MakeScene(Scene);
	m_pScene->Create();
}

HWND SceneManager::GetHWND() const
{
	return m_hWnd;
}

//シーン作成.
void SceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
	//case SceneManager::Title:
	//	m_pScene = std::make_unique<Title>();
	//	//BGMを止める.
	//	SoundManager::Stop(SoundManager::BGM_Over);
	//	SoundManager::Stop(SoundManager::BGM_Ending);
	//	//BGMのループ再生.
	//	SoundManager::PlayLoop(SoundManager::BGM_Title);
	//	break;
	case SceneManager::Main:
		m_pScene = std::make_unique<GameMain>();
		//SEを止める.
		//BGMを止める.
		SoundManager::Stop(SoundManager::BGM_Title);
		//BGMのループ再生.
		SoundManager::PlayLoop(SoundManager::BGM_Main);
		break;
	//case SceneManager::GameOver:
	//	m_pScene = std::make_unique<GameOver>();
	//	//BGMを止める.
	//	SoundManager::Stop(SoundManager::BGM_Main);
	//	//BGMループ.
	//	SoundManager::PlayLoop(SoundManager::BGM_Over);
	//	break;
	//case SceneManager::Ending:
	//	m_pScene = std::make_unique<Ending>();
	//	//BGMを止める.
	//	SoundManager::Stop(SoundManager::BGM_Main);
	//	//BGMループ.
	//	SoundManager::PlayLoop(SoundManager::BGM_Ending);
	//	break;
	default:
		break;
	}
}
