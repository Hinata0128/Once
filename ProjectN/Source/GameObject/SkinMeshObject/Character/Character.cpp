#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Update()
{
	SkinMeshObject::Update();
}

void Character::Draw(
	D3DXMATRIX& View,
	D3DXMATRIX& Proj,
	LIGHT& Light, 
	CAMERA& Camera)
{
	SkinMeshObject::Draw(View, Proj, Light, Camera);
}
