#include "SkinMeshManager.h"

SkinMeshManager::SkinMeshManager()
{
}

SkinMeshManager::~SkinMeshManager()
{
}

void SkinMeshManager::Create()
{
	for (int i = 0; i < static_cast<int>(SkinList::max); ++i)
	{
		m_pSkin[i] = std::make_unique<SkinMesh>();
	}
	struct MeshList
	{
		int listNo;
		const TCHAR path[256];
	};
	MeshList SList[] =
	{
		//ここに生成したいスキンメッシュの情報を書く.
		//{static_cast<int>(SkinList::Player), _T("Data\\Mesh\\Skin\\zako\\zako.x")},
		{static_cast<int>(SkinList::Player), _T("Data\\Mesh\\Skin\\EXTINGER\\extinger.X")},
	};
	int List_Max = sizeof(SList) / sizeof(SList[0]);
	for (int i = 0; i < List_Max; ++i)
	{
		int idx = SList[i].listNo;
		if (FAILED(m_pSkin[idx]->Init(SList[i].path)))
		{
			return;
		};
	}
}

void SkinMeshManager::Init()
{
}

SkinMesh* SkinMeshManager::GetSkinMeshInstance(SkinList SkinNo)
{
	return m_pSkin[static_cast<int>(SkinNo)].get();
}

SkinMeshManager* SkinMeshManager::GetInstance()
{
	static SkinMeshManager s_Instance;
	return &s_Instance;
}
