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

protected:
	int				m_AnimNo;			//アニメーション番号
	double			m_AnimTime;			//アニメーション経過時間
	double			m_AnimSpeed;		//アニメーション速度
	D3DXVECTOR3		m_BonePos;			//ボーン座標

	std::vector<std::unique_ptr<PShot>> m_pShotList;
	D3DXVECTOR3 m_ShotOffset; // 弾発射位置のオフセット
};