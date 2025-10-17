#pragma once
#include "GameObject/SkinMeshObject/Character/Character.h"

/**************************************************
*	�U�R�N���X
**/
class Player
	: public Character
{
public:
	Player();
	 ~Player() override;

	void Update() override;
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

protected:
	int				m_AnimNo;			//�A�j���[�V�����ԍ�
	double			m_AnimTime;			//�A�j���[�V�����o�ߎ���
	double			m_AnimSpeed;		//�A�j���[�V�������x
	D3DXVECTOR3		m_BonePos;			//�{�[�����W

};