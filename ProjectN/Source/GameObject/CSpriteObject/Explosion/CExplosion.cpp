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
	//�A�j���[�V���������ɏI�����Ă���ꍇ�́A����ȏ�̍X�V�͍s���܂���.
	if (m_bIsFinished)
	{
		return;
	}

	//�e�N���XCSpriteObject���X�v���C�g�������Ă��Ȃ��ꍇ�������𒆒f���܂�.
	if (m_pSprite == nullptr)
	{
		return;
	}

	//�X�v���C�g�V�[�g��X������Y�����̍ő�p�^�[����(�R�}��)���擾���܂�.
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
