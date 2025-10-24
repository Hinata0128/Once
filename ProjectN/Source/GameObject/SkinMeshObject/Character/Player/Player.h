#pragma once
#include <vector>
#include "GameObject/SkinMeshObject/Character/Character.h"

class PShot;
class PShotManager;

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
	void Draw() override;

	void SetAnimSpeed(double speed) { m_AnimSpeed = speed; }

	void Stop();

public:
	//W�ES�̑O�i��ޗp�֐�.
	D3DXVECTOR3 Player_WS() const;
	//A�ED�̍��E�p�֐�.
	D3DXVECTOR3 Player_AD() const;

protected:

	PShotManager*	m_pShotManager;
	D3DXVECTOR3		m_ShotOffset; // �e���ˈʒu�̃I�t�Z�b�g
};