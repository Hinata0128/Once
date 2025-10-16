#include "UIObject.h"

UIObject::UIObject()
	: m_pSprite		( nullptr )
	, m_PatternNo	()
{
}

UIObject::~UIObject()
{
	DetachSprite();
}

void UIObject::Update()
{
	if( m_pSprite == nullptr ){
		return;
	}
}

//引数なしのDraw()関数
void UIObject::Draw()
{
	if (m_pSprite == nullptr) 
	{
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->SetRotation(m_vRotation);
	m_pSprite->SetScale(m_vScale);

	//パターン番号を設定
	m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);

	//レンダリング.
	m_pSprite->Render();
}

//引数アリのDraw()関数
void UIObject::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera )
{
	Draw();
}