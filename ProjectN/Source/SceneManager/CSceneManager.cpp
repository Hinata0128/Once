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

	//�V�[���쐬.
	MakeScene(Scene);
	m_pScene->Create();
}

HWND CSceneManager::GetHWND() const
{
	return m_hWnd;
}

//�V�[���쐬.
void CSceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
	//case CSceneManager::Title:
	//	m_pScene = std::make_unique<CTitle>();
	//	//BGM���~�߂�.
	//	CSoundManager::Stop(CSoundManager::BGM_Over);
	//	CSoundManager::Stop(CSoundManager::BGM_Ending);
	//	//BGM�̃��[�v�Đ�.
	//	CSoundManager::PlayLoop(CSoundManager::BGM_Title);
	//	break;
	case CSceneManager::GameMain:
		m_pScene = std::make_unique<CGameMain>();
		//SE���~�߂�.
		//BGM���~�߂�.
		CSoundManager::Stop(CSoundManager::BGM_Title);
		//BGM�̃��[�v�Đ�.
		CSoundManager::PlayLoop(CSoundManager::BGM_Main);
		break;
	//case CSceneManager::GameOver:
	//	m_pScene = std::make_unique<CGameOver>();
	//	//BGM���~�߂�.
	//	CSoundManager::Stop(CSoundManager::BGM_Main);
	//	//BGM���[�v.
	//	CSoundManager::PlayLoop(CSoundManager::BGM_Over);
	//	break;
	//case CSceneManager::Ending:
	//	m_pScene = std::make_unique<CEnding>();
	//	//BGM���~�߂�.
	//	CSoundManager::Stop(CSoundManager::BGM_Main);
	//	//BGM���[�v.
	//	CSoundManager::PlayLoop(CSoundManager::BGM_Ending);
	//	break;
	default:
		break;
	}
}
