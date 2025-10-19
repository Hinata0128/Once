#pragma once
#include "StaticMash\\StaticMesh.h"

/**********************************************
*	スタティックメッシュマネージャークラス.
**/

class StaticMeshManager
{
public:
	//モデルの種類の列挙型.
	enum CMeshList
	{
		Bullet,
		Ground,
		Collision,

		max,
	};
public:
		~StaticMeshManager();

		void Create();
		void Init();

		//スタティッククラスのゲットインスタンスを書く
		StaticMesh* GetMeshInstance(CMeshList MeshNo)
		{
			return m_pMesh[MeshNo];
		};

		//インスタンス取得(唯一のアクセス経路).
		//※関数の前にstaticを付けることでインスタンス生成しなくても使用できる.
		static StaticMeshManager* GetInstance()
		{
			//唯一のインスタンスを作成する.
			//※staticで作成されたので2回目以降は、下の1行は無視される.
			static StaticMeshManager s_Instance;	//s_:staticの意味.
			return &s_Instance;
		}


private:
	//外部からコンストラクタへのアクセスを禁止する.
	StaticMeshManager();
	//コピーコンストラクタによるコピーを禁止する.
	//「=delete」で関数の定義を削除できる.
	StaticMeshManager(const StaticMeshManager& rhs) = delete;
	//代入演算子によるコピーを禁止する.
	//operator(オペレータ):演算子のオーバーロードで、演算の中身を拡張できる.
	StaticMeshManager& operator = (const StaticMeshManager& rhs) = delete;



	StaticMesh* m_pMesh[CMeshList::max];

};