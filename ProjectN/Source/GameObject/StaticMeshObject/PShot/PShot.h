#pragma once
#include "GameObject/StaticMeshObject/StaticMeshObject.h"
#include "Collision\\BoundingSphere.h"

class StaticMeshManager;

/******************************************************************
*	ショットクラス.
**/

class PShot
	: public StaticMeshObject
{
public:
	PShot();
	~PShot() override;

	void Update() override;
	void Draw() override;

	//弾の初期化.
	void Init();

	//リロードクラス.
	void Reload(const D3DXVECTOR3& pos, float speed);

	//プレイヤーの位置にバウンディングスフィアの中心を同期させる.
	void UpdateBPosition();

	//弾のバウンディングスフィアを取得する.
	std::shared_ptr<BoundingSphere> GetBoundingSphere();

	void SetDisplay(bool disp) { m_Disp = disp; }
	bool IsDisplay() const { return m_Disp; }


private:
	float	m_Speed;	//スピード.
	bool	m_Disp;		//弾を表示するかしないか.

	std::shared_ptr<BoundingSphere> m_pBSphere;
};