#pragma once
#include "GameObject//StaticMeshObject//ShotBase//ShotBase.h"

#include "GameObject//StaticMeshObject//StaticMeshObject.h"

/************************************************************
*	弾のベースクラス.
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
	//子クラスに必要になるメンバー変数をここに書いておく.
	D3DXVECTOR3 m_Direction;

	float	m_Speed;	//スピード.
	bool	m_Disp;		//弾を表示するかしないか.
	bool	m_IsActive;	//弾が生存しているか?
};