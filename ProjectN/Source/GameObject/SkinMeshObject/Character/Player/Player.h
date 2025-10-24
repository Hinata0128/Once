#pragma once
#include <vector>
#include "GameObject/SkinMeshObject/Character/Character.h"

class PShot;
class PShotManager;

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
	void Draw() override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void Stop();

public:
	//W・Sの前進後退用関数.
	D3DXVECTOR3 Player_WS() const;
	//A・Dの左右用関数.
	D3DXVECTOR3 Player_AD() const;

protected:

	PShotManager*	m_pShotManager;
	D3DXVECTOR3		m_ShotOffset; // 弾発射位置のオフセット
};