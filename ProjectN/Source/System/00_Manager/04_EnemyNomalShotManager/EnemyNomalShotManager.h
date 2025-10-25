#pragma once
#include <vector>

#include "..//..//..//GameObject/StaticMeshObject/ShotBase/EnemyNomalShot/EnemyNomalShot.h"

/*****************************************************************
*	敵の通常攻撃マネージャークラス.
**/

class EnemyNomalShotManager
{
public:
	~EnemyNomalShotManager();

	static EnemyNomalShotManager* GetInstance();

	void Update();
	void Draw();

	//敵の通常弾を作成して、管理リストに追加させる.
	void AddEnemyNomalShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton);

	void ReMoveEnemyNomalShot(size_t index);

	const std::vector<std::unique_ptr<EnemyNomalShot>>& GetEnemyNomalShot() const;

	EnemyNomalShot* GetEnemyNomalShot(size_t No);

	//敵の通常弾を取得.
	size_t GetEnemyNomalShotCount() const;
private:
	EnemyNomalShotManager();

	EnemyNomalShotManager(const EnemyNomalShotManager& rhs) = delete;
	EnemyNomalShotManager& operator = (const EnemyNomalShotManager& rhs) = delete;
private:
	static EnemyNomalShotManager* m_pInstance;	//シングルトンインスタンス.

	std::vector<std::unique_ptr<EnemyNomalShot>> m_EnemyNomalShot;
};