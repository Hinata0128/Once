#pragma once

#include "GameObject\GameObject.h"

#include "Sprite3D\Sprite3D.h"

/************************************************************
*	�X�v���C�g�I�u�W�F�N�g�N���X.
**/
class SpriteObject
	: public GameObject
{
public:
	SpriteObject();
	virtual ~SpriteObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	//SpriteObject�Ő錾�����֐��ŁA�ȍ~�����override������.
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj );

	//�X�v���C�g��ڑ�����.
	void AttachSprite(Sprite3D& pSprite ){
		m_pSprite = &pSprite;
	}
	//�X�v���C�g��؂藣��.
	void DetachSprite(){
		m_pSprite = nullptr;
	}

//�p�����̎q�N���X�ɂ��g����Draw()�֐�
protected:
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override final;

protected:
	Sprite3D*	m_pSprite;
};
