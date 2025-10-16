#include "Ending.h"
#include "Sound/SoundManager.h"

Ending::Ending()
	: CSceneBase		()
	, m_pEnding			( nullptr )
	, m_pSpriteEnding	( nullptr )
	, m_pEndingObj		( nullptr )
{

}

Ending::~Ending()
{
}

void Ending::Initialize()
{
}

void Ending::Create()
{
	m_pSpriteEnding = new Sprite2D();

	//タイトル構造体.
	Sprite2D::SPRITE_STATE SSTitle =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f };

	//タイトルスプライト読み込み.
	m_pSpriteEnding->Init(
		_T("Data\\Texture\\Ending.png"), SSTitle);

	//UIObjをインスタンス生成.
	m_pEndingObj = new UIObject();

	m_pEndingObj->AttachSprite(*m_pSpriteEnding);
}

void Ending::Update()
{
	SoundManager::Stop(SoundManager::BGM_Main);


}

void Ending::Draw()
{
	m_pEndingObj->Draw();
}
