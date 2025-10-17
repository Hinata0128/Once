#include "Shot.h"

Shot::Shot()
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
}

void Shot::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	StaticMeshObject::Draw(View, Proj, Light, Camera);
}
