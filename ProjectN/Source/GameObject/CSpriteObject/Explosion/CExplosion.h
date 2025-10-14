#pragma once
#include "GameObject\CSpriteObject\\CSpriteObject.h"

/**************************************************
*	爆発クラス.
**/

class CExplosion
	: public CSpriteObject	// スプライトオブジェクトクラスを継承
{
public:
	CExplosion();
	virtual ~CExplosion() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj ) override;

	void ResetAnimation(){
		m_PatternNo.x = 0;		//パターン番号X座標を0にリセット.
		m_PatternNo.y = 0;		//パターン番号Y座標を0にリセット.
		m_AnimCount = 0;		//アニメーションカウンタを0にリセット.
		m_bIsFinished = false;	//アニメーションが終了していない状態にリセット.
	}

	bool IsFinished() const { return m_bIsFinished; }

	virtual bool IsDisplay() const { return !m_bIsFinished; }

protected:
	POINTS	m_PatternNo;	// パターン番号(マス目)
	int		m_AnimCount;	// アニメーションカウント
	bool	m_bIsFinished;	//爆発アニメーションが最後まで再生されたかどうかを示すフラグ.
};

