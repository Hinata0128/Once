#include "Player.h"
#include "System/Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "..//..//..//StaticMeshObject/PShot/PShot.h"

Player::Player()
	: m_ShotOffset(0.0f, 0.5f, 1.0f)
{
	//AttachMesh(*SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player));
	SkinMesh* raw_mesh = SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player);

	auto shared_mesh = std::shared_ptr<SkinMesh>(raw_mesh,[](SkinMesh*){});

	//AttachMesh �� shared_ptr ��n��
	AttachMesh(shared_mesh);
	SetScale(0.04f);
	//SetScale(0.002f);
	SetPosition(0.f, 0.f, 2.f);

	//�A�j���[�V�����̑��x��
	m_AnimSpeed = 0.02f;
	//m_AnimSpeed = 0.0002f;

	//���̓v���C���[�N���X�Œe�̏o��o�Ȃ��̊m�F�������������̂ł����ɏ����Ă���.
	const int SHOT_COUNT = 10;
	m_pShotList.reserve(SHOT_COUNT); // ���������O�m��

	for (int i = 0; i < SHOT_COUNT; ++i)
	{
		auto shot = std::make_unique<PShot>();
		shot->Init();          // ������
		shot->SetDisplay(false); // ��\���ɂ��Ă���
		m_pShotList.push_back(std::move(shot));
	}
}

Player::~Player()
{
}

void Player::Update()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);

    constexpr float add_value = 0.1f;

    bool isMoving = false;  // �ړ����Ă��邩�t���O
    int newAnimNo = -1;     // ����Đ����ׂ��A�j���[�V����

    // �L�[���͂ɂ��ړ�
    if (GetAsyncKeyState('W') & 0x8000)
    {
        m_vPosition.z += add_value;
        isMoving = true;
        newAnimNo = 2;  // ����A�j���[�V����
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
        m_vPosition.z -= add_value;
        isMoving = true;
        newAnimNo = 0;  // ��ރA�j���[�V����
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        m_vPosition.x += add_value;
        isMoving = true;
        newAnimNo = 2;  // ����A�j���[�V����
    }
    else if (GetAsyncKeyState('A') & 0x8000)
    {
        m_vPosition.x -= add_value;
        isMoving = true;
        newAnimNo = 2;  // ����A�j���[�V����
    }

    // �ړ����Ă���ꍇ�̂݃A�j���[�V������؂�ւ�
    if (isMoving)
    {
        if (m_AnimNo != newAnimNo)
        {
            m_AnimNo = newAnimNo;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
    }
    else
    {
        // �ړ����Ă��Ȃ���Αҋ@�A�j���[�V����
        if (m_AnimNo != 0)  // �ҋ@�A�j���[�V������0�Ɖ���
        {
            m_AnimNo = 0;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
    }

    // �{�[�����W�̎擾
    m_pMesh->GetPosFromBone("head", &m_BonePos);

    // �e�̔���
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        // �ˌ��p�A�j���[�V����
        if (m_AnimNo != 2)  // ���Ɏˌ��A�j���[�V������2�Ƃ���
        {
            m_AnimNo = 2;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }

        for (auto& shot : m_pShotList)
        {
            if (!shot->IsDisplay())
            {
                D3DXMATRIX matS, matR, matT, playerWorldMatrix;
                D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
                D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
                D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
                D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
                D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

                D3DXVECTOR3 worldBonePos;
                D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);
                D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

                shot->Reload(shotPos, 0.2f);
                shot->SetDisplay(true);
                break;
            }
        }
    }

    // �e�̍X�V
    for (auto& shot : m_pShotList)
    {
        shot->Update();
    }

    // �A�j���[�V�����X�V
    m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);
}


void Player::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	Character::Draw(View, Proj, Light, Camera);

	for (auto& shot : m_pShotList)
	{
		shot->Draw(View, Proj, Light, Camera);
	}
}

void Player::Stop()
{
    if (m_pAnimCtrl)
    {
        // �A�j���[�V�����i�s���~�߂�
        m_pAnimCtrl->AdvanceTime(0.0f, nullptr);

        D3DXTRACK_DESC trackDesc;
        m_pAnimCtrl->GetTrackDesc(0, &trackDesc);
        trackDesc.Enable = FALSE;
        m_pAnimCtrl->SetTrackDesc(0, &trackDesc);
    }
}

