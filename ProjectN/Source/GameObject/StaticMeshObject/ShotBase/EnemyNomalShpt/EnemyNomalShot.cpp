#include "EnemyNomalShot.h"
#include "System/00_Manager/01_StaticMeshManager/StaticMeshManager.h"

EnemyNomalShot::EnemyNomalShot()
{
	//�G�̒e��ǂ�ł��܂�.
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::EnemyBullet));

	//������.
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
		//�ʒu�̍X�V.
		m_vPosition += m_Direction * m_Speed;

		//��苗���𒴂����烊�Z�b�g.
		if (D3DXVec3Length(&m_vPosition) >= MaxRange)
		{
			Init();
			return;
		}
		//�o�E���f�B���O�X�t�B�A�̈ʒu�̓���.
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
