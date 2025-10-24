#include "PShot.h"

#include "System\\00_Manager\\01_StaticMeshManager\\StaticMeshManager.h";

PShot::PShot()
	: m_Speed		( 0.02f )
	, m_Disp		( false )
	, m_IsActive	( false	)

	, m_pBSphere	(std::make_shared<BoundingSphere>())
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::Bullet));

	//�R���X�g���N�^�ŏ�����������.
	Init();
}

PShot::~PShot()
{
}

void PShot::Update()
{
	constexpr float Thirty = 30.0f;

	if (!m_IsActive) return;

	//true�̂Ƃ��ɓ���.
	if (m_Disp)
	{
		//Z���W�𑬓x�𑬓x����������������.
		m_vPosition += m_Direction * m_Speed;	//0.02�������Ă���.

		//��ʊO�ɍs�����Ƃ��ɏ���������.
		if (D3DXVec3Length(&m_vPosition) >= Thirty)
		{
			//�����Ȃ��Ȃ����e��������(�ė��p�\��Ԃɂ���).
			Init();
		}
		//�ʒu�𓯊�������.
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
	m_vPosition		= D3DXVECTOR3(0.0f, -50.0f, 0.0f); // ��ʊO�̏����ʒu
	m_vScale		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);     // �X�P�[�������Z�b�g
	m_vRotation		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // ��]�����Z�b�g

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
	D3DXVec3Normalize(&m_Direction, &m_Direction); // �����x�N�g���𐳋K��
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
