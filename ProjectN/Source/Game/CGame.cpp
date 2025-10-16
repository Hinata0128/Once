#include "CGame.h"
#include "Sound\\CSoundManager.h" // CSoundManager.hをインクルード
#include "Effect//Effect.h"
#include "StaticMash/CStaticMeshManager.h"

//コンストラクタ.
//初期化リストはメンバー変数の順番でする.
CGame::CGame( HWND hWnd )
	: m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
	// DirectX シングルトン取得
	auto pDx9 = CDirectX9::GetInstance();
	auto pDx11 = CDirectX11::GetInstance();
	//スタティックメッシュマネージャーの構築
	CStaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);
}


//デストラクタ.
CGame::~CGame()
{

}

//構築.
void CGame::Create()
{
	// DirectX シングルトン取得
	auto pDx9 = CDirectX9::GetInstance();
	auto pDx11 = CDirectX11::GetInstance();

	//スタティックメッシュマネージャーの構築
	CStaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);

	CSceneManager::GetInstance()->SetDx9(pDx9);
	CSceneManager::GetInstance()->SetDx11(pDx11);

	//Effectクラス
	//ここに書いておかないといけない
	//GameMainに書いてもいいけど先にLoadDateが読み込まされます.
	Effect::GetInstance()->Create(
		pDx11->GetDevice(),
		pDx11->GetContext());
}

//ロードデータ関数.
HRESULT CGame::LoadData()
{
	//サウンドデータの読み込み
	if (CSoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	//Effectクラス
	if (FAILED(Effect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	CSceneManager::GetInstance()->Create(m_hWnd);
	return S_OK;
}

//解放関数.
void CGame::Release()
{
}

//更新処理.
void CGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

//描画処理.
void CGame::Draw()
{
	CSceneManager::GetInstance()->Draw();
}

//ゲーム初期化/リセット用関数
void CGame::Init()
{
}