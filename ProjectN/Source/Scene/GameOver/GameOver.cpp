#include "GameOver.h"
#include "Sound/SoundManager.h"

GameOver::GameOver()
	: CSceneBase		()
	, m_pGameOver		( nullptr )
	, m_pSpriteGameOver	( nullptr )
	, m_pGameOverObj	( nullptr )
{

}

GameOver::~GameOver()
{
}

void GameOver::Initialize()
{
}

void GameOver::Create()
{
	m_pSpriteGameOver = new Sprite2D();

	//�^�C�g���\����.
	Sprite2D::SPRITE_STATE SSGameOver =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f };

	//�^�C�g���X�v���C�g�ǂݍ���.
	m_pSpriteGameOver->Init(
		_T("Data\\Texture\\GameOver.png"), SSGameOver);

	//UIObj���C���X�^���X����.
	m_pGameOverObj = new UIObject();

	m_pGameOverObj->AttachSprite(*m_pSpriteGameOver);
}

void GameOver::Update()
{
}

void GameOver::Draw()
{
	m_pGameOverObj->Draw();
}
