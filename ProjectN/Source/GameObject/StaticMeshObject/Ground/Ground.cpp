#include "Ground.h"
#include "System//Manager//StaticMeshManager//StaticMeshManager.h"

Ground::Ground()
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::CMeshList::Ground));

}

Ground::~Ground()
{
}

void Ground::Update()
{
}
