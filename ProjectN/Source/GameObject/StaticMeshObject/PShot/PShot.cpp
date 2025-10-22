#include "PShot.h"

#include "System\\Manager\\01_StaticMeshManager\\StaticMeshManager.h";

PShot::PShot()
	: m_Speed		( 0.02f )
	, m_Disp		( false )
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

	//true�̂Ƃ��ɓ���.
	if (m_Disp)
	{
		//Z���W�𑬓x�𑬓x����������������.
		m_vPosition.z += m_Speed;	//0.02�������Ă���.

		//��ʊQ�ɍs�����Ƃ��ɏ���������.
		if (m_vPosition.z >= Thirty)
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

	m_Disp = false; 
	m_Speed = 0.0f; 

	if (m_pBSphere) 
	{
		m_pBSphere->SetPosition(m_vPosition); 
		m_pBSphere->SetRadius(0.0f);          
	}
}

void PShot::Reload(const D3DXVECTOR3& pos, float speed)
{
	constexpr float TwoAndHal = 2.5f;

	//�e�̃T�C�Y��ύX.
	m_vScale	= D3DXVECTOR3(5.0f, 5.0f, 5.0f);
	//���ˈʒu�̐ݒ�.
	m_vPosition = pos;
	m_Speed		= speed;
	m_Disp		= false;

	//�Ĕ��˂̂Ƃ��Ƀo�E���f�B���O�X�t�B�A�̈ʒu�𓯊����Ĕ��a��ݒ肷��.
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
