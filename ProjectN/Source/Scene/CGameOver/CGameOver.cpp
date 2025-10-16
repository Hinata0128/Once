#include "CGameOver.h"
#include "Sound/CSoundManager.h"

CGameOver::CGameOver()
	: CSceneBase		()
	, m_pGameOver		( nullptr )
	, m_pSpriteGameOver	( nullptr )
	, m_pGameOverObj	( nullptr )
{

}

CGameOver::~CGameOver()
{
}

void CGameOver::Initialize()
{
}

void CGameOver::Create()
{
	m_pSpriteGameOver = new CSprite2D();

	//タイトル構造体.
	CSprite2D::SPRITE_STATE SSGameOver =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f };

	//タイトルスプライト読み込み.
	m_pSpriteGameOver->Init(
		_T("Data\\Texture\\GameOver.png"), SSGameOver);

	//UIObjをインスタンス生成.
	m_pGameOverObj = new CUIObject();

	m_pGameOverObj->AttachSprite(*m_pSpriteGameOver);
}

void CGameOver::Update()
{
}

void CGameOver::Draw()
{
	m_pGameOverObj->Draw();
}
