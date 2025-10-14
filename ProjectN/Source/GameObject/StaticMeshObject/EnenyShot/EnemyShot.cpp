#include "EnemyShot.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"

EnemyShot::EnemyShot()
    : m_vposition       (0, 0, 0)
    , m_velocity        (0, 0, 0)
    , m_speed           (0.f)
    , m_homingStrength  (0.f)
    , m_lifeTime        (0.f)
    , m_elapsedTime     (0.f)
    , m_pTargetPlayer   (nullptr)
    , m_bIsActive       (false)
{
    AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Shot));
}

EnemyShot::~EnemyShot()
{
}

void EnemyShot::Init(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer)
{
    m_vposition = position; //�����ʒu��ݒ�.
    SetPosition(position.x, position.y, position.z);

    //���������𐳋K��.
    D3DXVec3Normalize(&m_velocity, &initalDirection);
    //�e�̈ړ����x��ݒ�.
    m_speed = 3.f;
    //�������x�N�g���ɑ��x�������đ��x�x�N�g���ɂ���.
    m_velocity *= m_speed;

    //�z�[�~���O�̋���(0.0: ���i, 1.0: �u���Ƀ^�[�Q�b�g�̂ق���).
    //�������قǊɂ₩�ȃJ�[�u�ɂȂ�.
    m_homingStrength = 0.1f;
    m_lifeTime = 5.f;      //�e�̎�����10�b�Őݒ�.
    m_elapsedTime = 0.f;    //�o�ߎ��Ԃ����Z�b�g.

    m_pTargetPlayer = pTargetPlayer;    //�ǔ��Ώۂ��v���C���[�ɐݒ�.

    //�e���A�N�e�B�u��Ԃɂ���.
    m_bIsActive = true;
}

void EnemyShot::Update()
{
    if (!m_bIsActive)
    {
        return;
    }

    //�e�̎����̊Ǘ�.
    float deltaTime = 1.f / 100.f;

    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_lifeTime)
    {
        m_bIsActive = false;    //�������s�������A�N�e�B�u�ɂ���.
        return;                 //����ȏ�X�V���Ȃ�.
    }

    //�z�[�~���O���W�b�N.
    //�v���C���[���������Ă��鎞�̂ݒǔ�.
    if (m_pTargetPlayer)
    {
        D3DXVECTOR3 playerPos = m_pTargetPlayer->GetPosition();     //�v���C���[�̌��ݍ��W���擾.
        D3DXVECTOR3 toPlayer = playerPos - m_vposition;             //�v���C���[�ւ̐i�s�������x�N�g�����v�Z.

        D3DXVec3Normalize(&toPlayer, &toPlayer);    //�v���C���[�ւ̕����x�N�g���𐳋K��.

        // ���݂̑��x�x�N�g���ƃv���C���[�ւ̕����x�N�g������`��Ԃ��āA�z�[�~���O������.
        D3DXVECTOR3 newVelocityDirection;
        D3DXVECTOR3 currentDirection;
        D3DXVec3Normalize(&currentDirection, &m_velocity);

        D3DXVec3Lerp(&newVelocityDirection, &currentDirection, &toPlayer, m_homingStrength);
        //�ēx���K�����ĕ����x�N�g���ɂ���.
        D3DXVec3Normalize(&newVelocityDirection, &newVelocityDirection);
        //�V���������Ƒ����ő��x���X�V.
        m_velocity = newVelocityDirection * m_speed;
    }
    //�ʒu�̍X�V.
    m_vposition += m_velocity * deltaTime;
    //CStaticMeshObject�̈ʒu���X�V.
    SetPosition(m_vposition.x, m_vposition.y, m_vposition.z);
    //�����蔻����X�V.
    UpdateBSpherePos();
}

void EnemyShot::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //��A�N�e�B�u�Ȃ�\�����Ȃ�.
    if (!m_bIsActive)
    {
        return;
    }
    //�e�̃T�C�Y��ύX�ł���.
    m_vScale = D3DXVECTOR3(5.0f, 5.0f, 1.0f); // �e�̃X�P�[����ݒ�
    CStaticMeshObject::Draw(View, Proj, Light, Camera);
}
