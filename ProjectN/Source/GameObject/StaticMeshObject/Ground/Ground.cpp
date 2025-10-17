#include "Ground.h"
#include "StaticMash/StaticMeshManager.h"

Ground::Ground()
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::CMeshList::Ground));

}

Ground::~Ground()
{
}

void Ground::Update()
{
	//地面スクロールをここに書く
	//m_vPosition親クラスに書いているからポジションだけでいい.
	//地面の背景スクロールする用の処理
}
