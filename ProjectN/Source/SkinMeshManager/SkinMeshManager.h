#pragma once

#include "SkinMesh//SkinMesh.h"

/*****************************************************************************
*	スキンメッシュマネージャークラス
*	最終的には、アセットクラスを作成してそこにスタティックとスキンメッシュを統合させる.
*	今はシングルトンにしておきます.
**/

class SkinMeshManager
{
public:
	//スキンモデルの種類の列挙型.
	enum class SkinList
	{
		//ここに名前を書いていく.
		Player,

		max,
	};
public:
	~SkinMeshManager();

	void Create();
	void Init();

	//スキンメッシュクラスのGetInstanceを書く
	SkinMesh* GetSkinMeshInstance(SkinList SkinNo);

	static SkinMeshManager* GetInstance();
private:
	SkinMeshManager();
	SkinMeshManager(const SkinMeshManager& rhs) = delete;
	//コピーの禁止.
	SkinMeshManager& operator = (const SkinMeshManager& rhs) = delete;

	std::unique_ptr<SkinMesh> m_pSkin[static_cast<int>(SkinList::max)];

protected:

};
