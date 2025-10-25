#pragma once
#include <vector>
#include "GameObject/SkinMeshObject/Character/Character.h"

class PShot;
class PShotManager;
class Timer;

/**************************************************
*	�v���C���[�N���X.
**/
class Player final
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
	//W�ES�̑O�i��ޗp�֐�.
	D3DXVECTOR3 Player_WS() const;
	//A�ED�̍��E�p�֐�.
	D3DXVECTOR3 Player_AD() const;

private:

	PShotManager*	m_pShotManager;
};