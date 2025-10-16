#include "CSceneManager.h"
#include "Sound/CSoundManager.h"

CSceneManager::CSceneManager()
	: m_pScene	( nullptr )
	, m_hWnd	()
	, m_pDx11	()
	, m_pDx9	()
{

}

CSceneManager::~CSceneManager()
{
}

HRESULT CSceneManager::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	LoadScene(List::GameMain);
	return S_OK;
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::Draw()
{
	m_pScene->Draw();
}

void CSceneManager::LoadScene(List Scene)
{
	m_pScene.reset();

	//シーン作成.
	MakeScene(Scene);
	m_pScene->Create();
}

HWND CSceneManager::GetHWND() const
{
	return m_hWnd;
}

//シーン作成.
void CSceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
	//case CSceneManager::Title:
	//	m_pScene = std::make_unique<CTitle>();
	//	//BGMを止める.
	//	CSoundManager::Stop(CSoundManager::BGM_Over);
	//	CSoundManager::Stop(CSoundManager::BGM_Ending);
	//	//BGMのループ再生.
	//	CSoundManager::PlayLoop(CSoundManager::BGM_Title);
	//	break;
	case CSceneManager::GameMain:
		m_pScene = std::make_unique<CGameMain>();
		//SEを止める.
		//BGMを止める.
		CSoundManager::Stop(CSoundManager::BGM_Title);
		//BGMのループ再生.
		CSoundManager::PlayLoop(CSoundManager::BGM_Main);
		break;
	//case CSceneManager::GameOver:
	//	m_pScene = std::make_unique<CGameOver>();
	//	//BGMを止める.
	//	CSoundManager::Stop(CSoundManager::BGM_Main);
	//	//BGMループ.
	//	CSoundManager::PlayLoop(CSoundManager::BGM_Over);
	//	break;
	//case CSceneManager::Ending:
	//	m_pScene = std::make_unique<CEnding>();
	//	//BGMを止める.
	//	CSoundManager::Stop(CSoundManager::BGM_Main);
	//	//BGMループ.
	//	CSoundManager::PlayLoop(CSoundManager::BGM_Ending);
	//	break;
	default:
		break;
	}
}
