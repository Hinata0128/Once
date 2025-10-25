#include "Character.h"

Character::Character()
	: m_ShotOffset(0.0f, 1.5f, 1.0f)

	, m_ShotCoolDown(0.0f)
	//個々の初期化数値を設定することで発射レートが上がったり下がったりする.
	, m_CoolTime(0.0f)
{
}

Character::~Character()
{
}

void Character::Update()
{
	SkinMeshObject::Update();
}

void Character::Draw()
{
	SkinMeshObject::Draw();
}
