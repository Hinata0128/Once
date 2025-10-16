#pragma once

#include "GameObject\GameObject.h"

#include "Sprite3D\Sprite3D.h"

/************************************************************
*	スプライトオブジェクトクラス.
**/
class SpriteObject
	: public GameObject
{
public:
	SpriteObject();
	virtual ~SpriteObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	//SpriteObjectで宣言した関数で、以降これをoverrideさせる.
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj );

	//スプライトを接続する.
	void AttachSprite(Sprite3D& pSprite ){
		m_pSprite = &pSprite;
	}
	//スプライトを切り離す.
	void DetachSprite(){
		m_pSprite = nullptr;
	}

//継承元の子クラスにも使えるDraw()関数
protected:
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override final;

protected:
	Sprite3D*	m_pSprite;
};
