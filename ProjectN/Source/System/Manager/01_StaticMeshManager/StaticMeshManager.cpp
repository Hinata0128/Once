#include "StaticMeshManager.h"
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

StaticMeshManager::StaticMeshManager()
	: m_pMesh		()
{

}

StaticMeshManager::~StaticMeshManager()
{
}

void StaticMeshManager::Create()
{
	for (int i = 0; i < CMeshList::max; ++i)
	{
		m_pMesh[i] = new StaticMesh();
	}
	struct MeshList
	{
		int listNo;				//CMeshList�񋓌^��ݒ�.
		const TCHAR path[256];	//�t�@�C���̖��O(�p�X�t��).
	};
	MeshList MList[] =
	{

		{CMeshList::Bullet, 	_T("Data\\Mesh\\Static\\Bullet\\bullet.x")},
		{CMeshList::Ground,_T("Data\\Mesh\\Static\\Ground\\ground.x")},
	};
	int list_max = sizeof(MList) / sizeof(MList[0]);
	for (int i = 0; i < list_max; ++i)
	{
		if (FAILED(m_pMesh[i]->Init( MList[i].path ))) {

			return;
		};
	}
}

void StaticMeshManager::Init()
{
}