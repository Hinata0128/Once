#pragma once
#include "..//ShotBase.h"

class StaticMeshManager;

/**********************************************************************
*	“G’Êí’eƒNƒ‰ƒX.
**/

class EnemyNomalShot
	: public ShotBase
{
public:
	EnemyNomalShot();
	~EnemyNomalShot() override;

	void Update() override;
	void Draw() override;

	//’e‚Ì‰Šú‰».
	void Init() override;

	void Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed) override;

private:
};