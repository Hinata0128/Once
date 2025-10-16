#include "Title.h"
#include "Sound/SoundManager.h"

Title::Title()
	: CSceneBase				()
	, m_pTitle					( nullptr )
	, m_pSpriteTitle			( nullptr )
	, m_pTitleObj				( nullptr )
	
	, m_isTransitioning			()
	, m_transitionDelayTimer	()
{
	
}

Title::~Title()
{
}

void Title::Initialize()
{
	//遷移関連のフラグとタイマーをリセット
	m_isTransitioning = false;
	m_transitionDelayTimer = 0;
}

void Title::Create()
{
	m_pSpriteTitle = new Sprite2D();

	//タイトル構造体.
	Sprite2D::SPRITE_STATE SSTitle =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f};

	//タイトルスプライト読み込み.
	m_pSpriteTitle->Init(
		_T("Data\\Texture\\Title.png"), SSTitle);

	//UIObjをインスタンス生成.
	m_pTitleObj = new UIObject();

	m_pTitleObj->AttachSprite(*m_pSpriteTitle);
}

void Title::Update()
{
	if (m_isTransitioning)
	{
		m_transitionDelayTimer--; // タイマーを減らす
		if (m_transitionDelayTimer <= 0)
		{
			SceneManager::GetInstance()->LoadScene(SceneManager::Main); // GameMainシーンへ遷移
			m_isTransitioning = false; // フラグをリセット
			return; // シーン遷移後はこのフレームの残りのUpdate処理はスキップ
		}
		// 遷移演出中も描画は続けるので、Draw() は Update() 外で呼ばれる前提
		// ここで他の入力や更新処理を停止したいので return;
		return;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		SoundManager::PlaySE(SoundManager::SE_Enter); // SEを再生
		m_isTransitioning = true; // 遷移フラグを立てる
		m_transitionDelayTimer = TRANSITION_DELAY_FRAMES; // タイマーを開始
	}
}

void Title::Draw()
{
	m_pTitleObj->Draw();
}
