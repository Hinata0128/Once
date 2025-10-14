#include "CShot.h"
#include "Sound\\CSoundManager.h"      // ���ʉ��Đ��p
#include "StaticMash/CStaticMeshManager.h" // CStaticMeshManager�̃w�b�_�[

// CShot�N���X�̃R���X�g���N�^
CShot::CShot()
    : m_Disp    (false)   // �e�̕\����Ԃ�������
    , m_speed   (0.0f) // �e�̑��x��������
{
    AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Shot));


    // �o�E���f�B���O�X�t�B�A�̃C���X�^���X�𐶐� (�����蔻��p)
    m_pBSphere = new CBoundingSphere();

    Init(); // �e�̏�����Ԃ�ݒ� (�ʒu�A�X�P�[���A��\���Ȃ�)
}

// CShot�N���X�̃f�X�g���N�^
CShot::~CShot()
{
    // �o�E���f�B���O�X�t�B�A�̃C���X�^���X��j��
    SAFE_DELETE(m_pBSphere);
}

// �e�̏�Ԃ��X�V���郁�\�b�h�i���t���[���Ăяo�����j
void CShot::Update()
{
    if (m_Disp == true) // �e���\����ԁi�A�N�e�B�u�j�̏ꍇ�̂ݍX�V
    {
        // Z���W�𑬓x���������������� (�������֐i��)
         m_vPosition.z += m_speed + 0.1f; // 0.1f �͍Œᑬ�x�܂��͔������p

        // �e����ʊO�ɏo�����ǂ����̔���
        // ��ʂ�Y���AX�������̒[���l�����āA���S�ɉ�ʊO�ɏo�����\���ɖ߂�
        if (m_vPosition.z >= 30.0 )
        {
            Init(); // ��ʊO�ɏo���珉����Ԃɖ߂��A�ė��p�\�ɂ���
        }

        // �o�E���f�B���O�X�t�B�A�̈ʒu�����g�̈ʒu�ɓ���������
        UpdateBoundingSpherePosition();
    }
}

// �e��`�悷�郁�\�b�h
void CShot::Draw(
    D3DXMATRIX& View, D3DXMATRIX& Proj,
    LIGHT& light, CAMERA& camera)
{
    if (m_Disp == true) // �e���\����Ԃ̏ꍇ�̂ݕ`��
    {
        // �e�N���XCStaticMeshObject��Draw���\�b�h���Ăяo���A���ۂ̕`����s��
        CStaticMeshObject::Draw(View, Proj, light, camera);
    }
}

// �e�𔭎ˏ�Ԃɂ��郁�\�b�h
void CShot::Reload(const D3DXVECTOR3& Pos, float speed)
{
    //�e�̃T�C�Y�������Œ����ł���.
    m_vScale = D3DXVECTOR3(1.0f, 1.0f, 5.0f); // �e�̃X�P�[����ݒ�
    m_vPosition = Pos;                     // ���ˈʒu��ݒ�
    m_speed = speed;                       // �e�̑��x��ݒ�
    m_Disp = true;                         // �e��\����Ԃɂ���

    // �����[�h���Ƀo�E���f�B���O�X�t�B�A�̈ʒu�𓯊����A���a��ݒ�
    if (m_pBSphere) {
        m_pBSphere->SetRadius(0.5f);      // ���̔��a�l�B�e�̑傫���ɍ��킹�Ē������Ă�������
        m_pBSphere->SetPosition(m_vPosition); // ���ˈʒu�ɍ��킹��
    }

}

// �e��������Ԃɖ߂����\�b�h�i��\���A��ʊO�ֈړ��Ȃǁj
void CShot::Init()
{
    m_vPosition = D3DXVECTOR3(0.0f, -1000.0f, 0.0f); // ��ʊO�̏����ʒu
    m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);     // �X�P�[�������Z�b�g
    m_vRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // ��]�����Z�b�g

    m_Disp = false; // ��\����Ԃɂ���
    m_speed = 0.0f; // ���x�����Z�b�g

    // ���������Ƀo�E���f�B���O�X�t�B�A�̈ʒu�����Z�b�g���A�����蔻��𖳌���
    if (m_pBSphere) {
        m_pBSphere->SetPosition(m_vPosition); // ��\���̈ʒu�ɍ��킹��
        m_pBSphere->SetRadius(0.0f);          // �����蔻��𖳌��� (���a��0�ɂ���)
    }
}

// �o�E���f�B���O�X�t�B�A�̈ʒu�����g�̈ʒu�ɓ���������֐�
void CShot::UpdateBoundingSpherePosition() {
    if (m_pBSphere) {
        m_pBSphere->SetPosition(m_vPosition);
    }
}