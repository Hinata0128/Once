#include "ShotBase.h"

ShotBase::ShotBase()
	: m_Speed(0.02f)
	, m_Disp(false)
	, m_IsActive(false)
	, m_BSphere(std::make_shared<BoundingSphere>())
{
}

ShotBase::~ShotBase()
{
}

void ShotBase::Update()
{
	// �K�v�Ȃ狤�ʂ̒e�ړ������������ɏ����i����͎q�N���X�C���j
	StaticMeshObject::Update();
}

void ShotBase::Draw()
{
	// �\�����̂ݕ`��
	if (m_Disp)
	{
		StaticMeshObject::Draw();
	}
}

void ShotBase::Init()
{
	m_vPosition = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	m_vScale	= D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Disp		= false;
	m_IsActive	= false;
		
	if (m_BSphere)
	{
		m_BSphere->SetPosition(m_vPosition);
		m_BSphere->SetRadius(0.0f);
	}
}

void ShotBase::UpdateBPosition()
{
	if (m_BSphere)
	{
		m_BSphere->SetPosition(m_vPosition);
	}
}

std::shared_ptr<BoundingSphere> ShotBase::GetBoundingSphere()
{
	return m_BSphere;
}
