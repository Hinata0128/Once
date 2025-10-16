#pragma once

#include "GameObject\\GameObject.h"
#include "Sprite2D\Sprite2D.h"

/************************************************************
*	UI�I�u�W�F�N�g�N���X.
**/
class UIObject
	: public GameObject
{
public:
	UIObject();
	virtual ~UIObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	//CUIObject�Ő錾�����֐��ŁA�ȍ~�͂����override������.
	virtual void Draw();

	//�X�v���C�g��ڑ�����.
	void AttachSprite(Sprite2D& pSprite ){
		m_pSprite = &pSprite;
	}
	//�X�v���C�g��؂藣��.
	void DetachSprite(){
		m_pSprite = nullptr;
	}
	//�p�^�[���ԍ���ݒ�
	void SetPatternNo(SHORT x, SHORT y)
	{
		m_PatternNo.x = x;
		m_PatternNo.y = y;
	}

protected:
	//CGameObject����p�������֐�.
	//final : ����ȍ~��override�����Ȃ�.
	 void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override final;

protected:
	Sprite2D*	m_pSprite;
	POINTS		m_PatternNo;	//�p�^�[���ԍ�(�}�X��)
};
