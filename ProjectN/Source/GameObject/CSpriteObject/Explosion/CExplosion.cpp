#include "CExplosion.h"

CExplosion::CExplosion()
	: m_PatternNo	()
	, m_AnimCount	(0)
	, m_bIsFinished	(false)
{
}

CExplosion::~CExplosion()
{
}

void CExplosion::Update()
{
	//アニメーションが既に終了している場合は、それ以上の更新は行いません.
	if (m_bIsFinished)
	{
		return;
	}

	//親クラスCSpriteObjectがスプライトを持っていない場合も処理を中断します.
	if (m_pSprite == nullptr)
	{
		return;
	}

	//スプライトシートのX方向とY方向の最大パターン数(コマ数)を取得します.
	const POINTS PatternMAX = m_pSprite->GetPatternMax();

	m_AnimCount++;
	if ( m_AnimCount % 10 == 0 )
	{
		m_PatternNo.x = (m_AnimCount / 10) % PatternMAX.x;
		m_PatternNo.y = (m_AnimCount / 10) / PatternMAX.y;
	}
	if ( m_AnimCount / 10 >= PatternMAX.x * PatternMAX.y )
	{
		m_AnimCount = 0;
		m_bIsFinished = true;
	}
}

void CExplosion::Draw( D3DXMATRIX& View, D3DXMATRIX& Proj )
{
	if (m_pSprite == nullptr || m_bIsFinished)
	{
		return;
	}

	m_pSprite->SetPatternNo(m_PatternNo.x, m_PatternNo.y);

	m_pSprite->SetBillboard( true );

	CSpriteObject::Draw( View, Proj );

	m_pSprite->SetBillboard( false );
}
