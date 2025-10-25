#pragma once
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyBase.h"	//ベースクラス.

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
	//W・Sの前進後退用関数.
	D3DXVECTOR3 Enemy_WS() const;

private:
	EnemyNomalShotManager* m_pENShotManager;
};