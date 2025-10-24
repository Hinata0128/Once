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

	//リロード.
	void Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed);

	//プレイヤーの位置にバウンディングスフィアの中心を同期させる.
	void UpdateBPosition();

	//弾のバウンディングスフィアを取得する.
	std::shared_ptr<BoundingSphere> GetBoundingSphere();

	void SetDisplay(bool disp) { m_Disp = disp; }
	bool IsDisplay() const { return m_Disp; }

	//Playerの弾が生存しているかをManagerにわたす.
	bool IsActive() const;


private:
	D3DXVECTOR3 m_Direction;

	float	m_Speed;	//スピード.
	bool	m_Disp;		//弾を表示するかしないか.
	bool	m_IsActive;	//弾が生存しているか?

	std::shared_ptr<BoundingSphere> m_pBSphere;
};