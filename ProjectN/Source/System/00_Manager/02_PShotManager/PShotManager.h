#pragma once
#include <vector>	//弾を生成と破棄をしている.

#include "..//..//..//GameObject/StaticMeshObject/PShot/PShot.h"


class PShotManager
{
public:
	~PShotManager();

	static PShotManager* GetInstance();

	void Update();
	void Draw();

	//プレイヤーの通常弾を作成して、管理リストに追加させる.
	void AddPlayerShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton);

	void ReMovePlayerShot(size_t index);

	const std::vector<std::unique_ptr<PShot>>& GetPlayerShot() const;

	PShot* GetPlayrShot(size_t No);

	//プレイヤーの弾を取得.
	size_t GetPlayerShotCount() const;
private:
	PShotManager();

	PShotManager(const PShotManager& rhs) = delete;
	PShotManager& operator = (const PShotManager& rhs) = delete;

private:
	static PShotManager* m_pInstance;	//シングルトンインスタンス.

	std::vector<std::unique_ptr<PShot>> m_PlayerShot;
};