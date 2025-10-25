#include "EnemyNomalShot.h"
#include "System/00_Manager/01_StaticMeshManager/StaticMeshManager.h"

EnemyNomalShot::EnemyNomalShot()
{
	//敵の弾を読んでいます.
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::EnemyBullet));

	//初期化.
	Init();
}

EnemyNomalShot::~EnemyNomalShot()
{
}

void EnemyNomalShot::Update()
{
	constexpr float MaxRange = 30.0f;

	if (!m_IsActive) return;

	if (m_Disp)
	{
		//位置の更新.
		m_vPosition += m_Direction * m_Speed;

		//一定距離を超えたらリセット.
		if (D3DXVec3Length(&m_vPosition) >= MaxRange)
		{
			Init();
			return;
		}
		//バウンディングスフィアの位置の同期.
		UpdateBPosition();
	}
}

void EnemyNomalShot::Draw()
{
}

void EnemyNomalShot::Init()
{
}

void EnemyNomalShot::Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed)
{
}
