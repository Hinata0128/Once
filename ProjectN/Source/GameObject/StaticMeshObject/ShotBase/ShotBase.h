#pragma once
#include "GameObject//StaticMeshObject//ShotBase//ShotBase.h"

#include "GameObject//StaticMeshObject//StaticMeshObject.h"

/************************************************************
*	�e�̃x�[�X�N���X.
**/

class ShotBase
	: public StaticMeshObject
{
public:
	ShotBase();
	virtual ~ShotBase() override;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Init();
protected:
	//�q�N���X�ɕK�v�ɂȂ郁���o�[�ϐ��������ɏ����Ă���.
	D3DXVECTOR3 m_Direction;

	float	m_Speed;	//�X�s�[�h.
	bool	m_Disp;		//�e��\�����邩���Ȃ���.
	bool	m_IsActive;	//�e���������Ă��邩?
};