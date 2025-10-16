#include "Character.h"

Character::Character()
	: m_Shot		( false )
{
}

Character::~Character()
{
}

void Character::Update()
{
	StaticMeshObject::Update();
}

void Character::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera )   
{ 
	StaticMeshObject::Draw( View, Proj, Light, Camera );
}

bool Character::IsShot(int No) const
{
	if (0 >= ShotMax) { return false; }
	return m_Shot[No];
}
