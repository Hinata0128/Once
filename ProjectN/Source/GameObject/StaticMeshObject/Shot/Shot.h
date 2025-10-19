#pragma once
#include "GameObject/StaticMeshObject/StaticMeshObject.h"

class StaticMeshManager;

/******************************************************************
*	ショットクラス.
**/

class Shot
	: public StaticMeshObject
{
public:
	Shot();
	~Shot() override;

	void Update() override;
	void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	//弾の初期化.
	void Init();

	//リロードクラス.
	void Reload(const D3DXVECTOR3& pos, float speed);


private:
	float m_Speed;	//スピード.
};