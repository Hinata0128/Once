#pragma once
#include "GameObject/SkinMeshObject/SkinMeshObject.h"

/************************************************************
*	キャラクタークラス.
**/

class Character
	: public SkinMeshObject
{
public:
	Character();
	virtual ~Character() override;

	virtual void Update() override;
	virtual void Draw() override;
protected:
	D3DXVECTOR3		m_ShotOffset; // 弾発射位置のオフセット

	//弾のクールタイム実装.
	float m_ShotCoolDown;
	float m_CoolTime;

};