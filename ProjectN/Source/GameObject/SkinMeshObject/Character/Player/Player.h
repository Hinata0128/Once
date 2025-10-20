#pragma once
#include <vector>
#include "GameObject/SkinMeshObject/Character/Character.h"

class PShot;

/**************************************************
*	ザコクラス
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

	void Stop();

protected:

	std::vector<std::unique_ptr<PShot>> m_pShotList;
	D3DXVECTOR3 m_ShotOffset; // 弾発射位置のオフセット
};