#pragma once
#include "GameObject//SkinMeshObject//Character//Character.h"

/************************************************************************
*	敵ベースクラス.
*	これを基底クラスにして作成していきます.
**/

class EnemyBase
	: public Character
{
public:
	EnemyBase();
	virtual ~EnemyBase() override;

	virtual void Update() override;
	virtual void Draw() override;

protected:
	//今はまだ必要がないので書かない.
};