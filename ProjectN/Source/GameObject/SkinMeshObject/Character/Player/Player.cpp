#include "Player.h"
#include "System/Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "..//..//..//StaticMeshObject/PShot/PShot.h"

Player::Player()
	: m_AnimNo()
	, m_AnimTime()
	, m_AnimSpeed(0.0002)
	, m_BonePos()
	, m_ShotOffset(0.0f, 0.5f, 1.0f)
{
	AttachMesh(*SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player));
	SetScale(0.02f);
	SetPosition(0.f, 0.f, 2.f);

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

	if (GetAsyncKeyState('W') & 0X8000)
	{
		m_vPosition.z += add_value;
	}
	if (GetAsyncKeyState('S') & 0X8000)
	{
		m_vPosition.z -= add_value;
	}
	if (GetAsyncKeyState('D') & 0X8000)
	{
		m_vPosition.x += add_value;
	}
	if (GetAsyncKeyState('A') & 0X8000)
	{
		m_vPosition.x -= add_value;
	}

	//�A�j���[�V�����ؑ�
	if (GetAsyncKeyState('N') & 0x8000)
	{
		m_AnimNo = 2;		//�o��A�j���[�V����
		m_AnimTime = 0.0;	//�A�j���[�V�����o�ߎ��ԏ�����
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}
	if (m_AnimNo == 2)
	{
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_AnimSpeed;

		//�o��A�j���[�V�����̏I�����Ԃ𒴂����H
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 0;		//�ҋ@�A�j���[�V������
			m_AnimTime = 0.0;	//�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}
	if (m_AnimNo == 0)
	{
		//�A�j���[�V�����o�ߎ��Ԃ����Z
		m_AnimTime += m_AnimSpeed;

		//�o��A�j���[�V�����̏I�����Ԃ𒴂����H
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 1;		//�����A�j���[�V������
			m_AnimTime = 0.0;	//�A�j���[�V�����o�ߎ��ԏ�����
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}
	//�{�[�����W�̎擾
	m_pMesh->GetPosFromBone("blade_l_head", &m_BonePos);
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for (auto& shot : m_pShotList)
		{
			if (!shot->IsDisplay())
			{
				// 1. �e�ϊ��s����ʂɍ쐬����
				D3DXMATRIX matS, matR, matT;
				D3DXMATRIX playerWorldMatrix;

				// �X�P�[���s��̍쐬
				D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

				// ��]�s��̍쐬 (m_vRotation���I�C���[�p�Ƃ��Ďg�p)
				D3DXMatrixRotationYawPitchRoll(
					&matR,
					m_vRotation.y, m_vRotation.x, m_vRotation.z
				);

				// �ړ��s��̍쐬
				D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

				// 2. ���[���h�s����\�z���� (S * R * T �̏��ɏ�Z)
				// S��R�ŕϊ����A���̌��ʂ�T�ŕϊ�����
				D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
				D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

				// 3. ���[�J���̃{�[�����W�����[���h���W�ɕϊ�����
				D3DXVECTOR3 worldBonePos;
				D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);

				// 4. ���[���h���W�ɃI�t�Z�b�g�������āA�ŏI�I�Ȕ��ˈʒu������
				D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

				// 5. �e�𔭎�
				shot->Reload(shotPos, 0.2f);
				shot->SetDisplay(true);
				break;
			}
		}
	}

	for (auto& shot : m_pShotList)
	{
		shot->Update();
	}
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
