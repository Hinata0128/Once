#include "PShot.h"

#include "System\\00_Manager\\01_StaticMeshManager\\StaticMeshManager.h";

PShot::PShot()
	: m_Speed		( 0.02f )
	, m_Disp		( false )
	, m_IsActive	( false	)

	, m_pBSphere	(std::make_shared<BoundingSphere>())
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::Bullet));

	//コンストラクタで初期化をする.
	Init();
}

PShot::~PShot()
{
}

void PShot::Update()
{
	constexpr float Thirty = 30.0f;

	if (!m_IsActive) return;

	//trueのときに入る.
	if (m_Disp)
	{
		//Z座標を速度を速度分だけ加速させる.
		m_vPosition += m_Direction * m_Speed;	//0.02ずつ増えていく.

		//画面外に行ったときに初期化する.
		if (D3DXVec3Length(&m_vPosition) >= Thirty)
		{
			//見えなくなった弾を初期化(再利用可能状態にする).
			Init();
		}
		//位置を同期させる.
		UpdateBPosition();
	}
}

void PShot::Draw()
{
	if (m_Disp)
	{
		StaticMeshObject::Draw();
	}
}

void PShot::Init()
{
	m_vPosition		= D3DXVECTOR3(0.0f, -50.0f, 0.0f); // 画面外の初期位置
	m_vScale		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);     // スケールをリセット
	m_vRotation		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 回転をリセット

	m_Disp		= false;
	m_IsActive	= false;

	if (m_pBSphere) 
	{
		m_pBSphere->SetPosition(m_vPosition); 
		m_pBSphere->SetRadius(0.0f);          
	}
}

void PShot::Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed)
{
	constexpr float TwoAndHal = 2.5f;

	m_vScale = D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	m_vPosition = pos;
	m_Direction = direction;
	D3DXVec3Normalize(&m_Direction, &m_Direction); // 方向ベクトルを正規化
	m_Speed = speed;
	m_Disp = true;
	m_IsActive = true;

	if (m_pBSphere)
	{
		m_pBSphere->SetRadius(TwoAndHal);
		m_pBSphere->SetPosition(m_vPosition);
	}
}
void PShot::UpdateBPosition()
{
	if (m_pBSphere)
	{
		m_pBSphere->SetPosition(m_vPosition);
	}
}

std::shared_ptr<BoundingSphere> PShot::GetBoundingSphere()
{
	return m_pBSphere;
}

bool PShot::IsActive() const
{
	return m_IsActive;
}
