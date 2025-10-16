#include "Game.h"
#include "Sound\\SoundManager.h" // SoundManager.hをインクルード
#include "Effect//Effect.h"
#include "StaticMash/StaticMeshManager.h"

//コンストラクタ.
//初期化リストはメンバー変数の順番でする.
Game::Game( HWND hWnd )
	: m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
	// DirectX シングルトン取得
	auto pDx9 = DirectX9::GetInstance();
	auto pDx11 = DirectX11::GetInstance();
	//スタティックメッシュマネージャーの構築
	StaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);
}


//デストラクタ.
Game::~Game()
{

}

//構築.
void Game::Create()
{
	// DirectX シングルトン取得
	auto pDx9 = DirectX9::GetInstance();
	auto pDx11 = DirectX11::GetInstance();

	//スタティックメッシュマネージャーの構築
	StaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);

	SceneManager::GetInstance()->SetDx9(pDx9);
	SceneManager::GetInstance()->SetDx11(pDx11);

	//Effectクラス
	//ここに書いておかないといけない
	//GameMainに書いてもいいけど先にLoadDateが読み込まされます.
	Effect::GetInstance()->Create(
		pDx11->GetDevice(),
		pDx11->GetContext());
}

//ロードデータ関数.
HRESULT Game::LoadData()
{
	//サウンドデータの読み込み
	if (SoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	//Effectクラス
	if (FAILED(Effect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	SceneManager::GetInstance()->Create(m_hWnd);
	return S_OK;
}

//解放関数.
void Game::Release()
{
}

//更新処理.
void Game::Update()
{
	SceneManager::GetInstance()->Update();
}

//描画処理.
void Game::Draw()
{
	SceneManager::GetInstance()->Draw();
}

//ゲーム初期化/リセット用関数
void Game::Init()
{
}