#include "CEnemyShotManager.h"

CEnemyShotManager* CEnemyShotManager::m_pInstance = nullptr;

CEnemyShotManager::CEnemyShotManager()
{
}

CEnemyShotManager::~CEnemyShotManager()
{
    ClearAllHomingShot();
}

CEnemyShotManager* CEnemyShotManager::GetInstance()
{
    //�C���X�^���X���܂���������Ă��Ȃ���ΐV������������.
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CEnemyShotManager();
    }
    return m_pInstance;
}

//�S�Ẵz�[�~���O�e���X�V����.
void CEnemyShotManager::Update()
{
    //�C�e���[�^���g���ă��[�v���邱�ƂŁA�r���ŗv�f���폜����.
    for (auto it = m_homingShots.begin(); it != m_homingShots.end();)
    {
        (*it)->Update();    //�e�z�[�~���O�e��Update�֐����Ăяo��.

        //�z�[�~���O�e����A�N�e�B�u(�����؂��Փ˂Ȃ�)�ɂȂ�����폜����.
        if (!(*it)->IsActive())
        {
            delete* it; //�q�[�v����������e�̃I�u�W�F�N�g�����.
            it = m_homingShots.erase(it);   //vector����|�C���^���폜���A���̃C�e���[�^���擾
        }
        else
        {
            ++it;   //���̃z�[�~���O�e�֐i��.
        }
    }
}

void CEnemyShotManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //m_homingShots�̔z��̍ŏ�����Ō�܂ł��񂷁B����for���ŏ����ƃI�[�o�[�t���[�����Ȃ��悤�ɂ��闘�_������B
    for (EnemyShot* shot : m_homingShots)
    {
        if (shot->IsActive())
        {
            shot->Draw(View, Proj, Light, Camera);
        }
    }
}

//�V�����z�[�~���O�e���쐬���A�Ǘ����X�g�ɒǉ�����.
void CEnemyShotManager::AddHomingShot(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer)
{
    EnemyShot* newShot = new EnemyShot();

    //���������e��������.
    newShot->Init(position, initalDirection, pTargetPlayer);

    //�Ǘ����X�g�ɒǉ�.
    m_homingShots.push_back(newShot);
}

//�S�Ẵz�[�~���O�e�����X�g����폜���A���������������.
void CEnemyShotManager::ClearAllHomingShot()
{
    for (EnemyShot* shot : m_homingShots)
    {
        SAFE_DELETE (shot);    //�e�e�̃����������.
    }
    m_homingShots.clear();  //vector�̒��g���N���A.
}

void CEnemyShotManager::RemoveShot(size_t index)
{
    if (index < m_homingShots.size())
    {
        SAFE_DELETE(m_homingShots[index]);   //�I�u�W�F�N�g�̉��.
        m_homingShots.erase(m_homingShots.begin() + index);   //�R���e�i����v�f���폜.
    }

}

void CEnemyShotManager::Init()
{
    ClearAllHomingShot();
}
