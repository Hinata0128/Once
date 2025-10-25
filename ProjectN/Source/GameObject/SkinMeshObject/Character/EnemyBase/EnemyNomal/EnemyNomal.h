#pragma once
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyBase.h"	//�x�[�X�N���X.

class EnemyNomalShotManager;
class Timer;

class EnemyNomal final
	: EnemyBase
{
public:
	EnemyNomal();
	~EnemyNomal() override;

	void Update() override;
	void Draw() override; 

	void SetAnimSpeed(double speed);

	void Stop();

public:
	//W�ES�̑O�i��ޗp�֐�.
	D3DXVECTOR3 Enemy_WS() const;

private:
	EnemyNomalShotManager* m_pENShotManager;
};