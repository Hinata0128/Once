#pragma once
#include "GameObject//SkinMeshObject//Character//EnemyBase//EnemyBase.h"	//�x�[�X�N���X.

class SkinMeshManager;

class EnemyNomal final
	: EnemyBase
{
public:
	EnemyNomal();
	~EnemyNomal() override;

	void Update() override;
	void Draw() override; 

private:

};