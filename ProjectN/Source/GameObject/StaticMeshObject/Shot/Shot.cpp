#include "Shot.h"

#include "System\\Manager\\01_StaticMeshManager\\StaticMeshManager.h";

Shot::Shot()
	: m_Speed	(0.02f)
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::Bullet));
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

void Shot::Init()
{

}

void Shot::Reload(const D3DXVECTOR3& pos, float speed)
{
}
