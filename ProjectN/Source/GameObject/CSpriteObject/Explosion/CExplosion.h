#pragma once
#include "GameObject\CSpriteObject\\CSpriteObject.h"

/**************************************************
*	�����N���X.
**/

class CExplosion
	: public CSpriteObject	// �X�v���C�g�I�u�W�F�N�g�N���X���p��
{
public:
	CExplosion();
	virtual ~CExplosion() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj ) override;

	void ResetAnimation(){
		m_PatternNo.x = 0;		//�p�^�[���ԍ�X���W��0�Ƀ��Z�b�g.
		m_PatternNo.y = 0;		//�p�^�[���ԍ�Y���W��0�Ƀ��Z�b�g.
		m_AnimCount = 0;		//�A�j���[�V�����J�E���^��0�Ƀ��Z�b�g.
		m_bIsFinished = false;	//�A�j���[�V�������I�����Ă��Ȃ���ԂɃ��Z�b�g.
	}

	bool IsFinished() const { return m_bIsFinished; }

	virtual bool IsDisplay() const { return !m_bIsFinished; }

protected:
	POINTS	m_PatternNo;	// �p�^�[���ԍ�(�}�X��)
	int		m_AnimCount;	// �A�j���[�V�����J�E���g
	bool	m_bIsFinished;	//�����A�j���[�V�������Ō�܂ōĐ����ꂽ���ǂ����������t���O.
};

