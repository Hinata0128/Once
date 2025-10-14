#include "CPlayer.h"
#include "Sound\\CSoundManager.h" // �K�v�ł���Ό��ʉ��}�l�[�W���[

// CPlayer�N���X�̃R���X�g���N�^
CPlayer::CPlayer()
	: m_ShotCoolDown(0) // �N�[���_�E���J�E���^�[��������
	// �R���X�g���N�^���������X�g�ł� m_pShot(0) �͔z��ɂ͕s�v�Ȃ̂ō폜���܂���
{
	// ShotMax��CShot�I�u�W�F�N�g�𓮓I�ɐ������A�|�C���^�z��Ɋi�[
	// CPlayer.h �� ShotMax ����`����Ă��邱�Ƃ��m�F���Ă������� (��: const int ShotMax = 10;)
	for (int i = 0; i < ShotMax; ++i)
	{
		m_pShot[i] = new CShot();
	}
}

// CPlayer�N���X�̃f�X�g���N�^
CPlayer::~CPlayer()
{
	//���������[�N��h�����߁Anew����CShot�I�u�W�F�N�g�����
	for (int i = 0; i < ShotMax; ++i)
	{
		if (m_pShot[i] != nullptr) // nullptr�`�F�b�N�͈��S�̂���
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr; // �����A�|�C���^��nullptr�ɐݒ�
		}
	}
}

// �v���C���[�̏�Ԃ��X�V���郁�\�b�h�i���t���[���Ăяo�����z��j
void CPlayer::Update()
{
	float add_value = 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000) {

		if (m_vPosition.y <= WallUP)
		{
			m_vPosition.y += add_value;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (m_vPosition.y >= WallDOWN)
		{
			m_vPosition.y -= add_value;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (m_vPosition.x <= WallRIGHT)
		{
			m_vPosition.x += add_value;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (m_vPosition.x >= WallLEFT)
		{
			m_vPosition.x -= add_value;
		}
	}

	// 'Z'�L�[�������ꂽ���̒e�̔��ˏ���
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		// �N�[���_�E�����I�����Ă���ꍇ�i�N�[���_�E���J�E���^�[��0�ȉ��j�̂ݔ��˂����݂�
		if (m_ShotCoolDown <= 0)
		{
			// ���g�p�̒e�i��\����Ԃ̒e�j��T��
			CShot* pAvaillableShot = UnusedBullet();

			// ���g�p�̒e�����������ꍇ
			if (pAvaillableShot != nullptr)
			{
				// Reload���\�b�h�ɃX�s�[�h���n���B�e�̃X�s�[�h��0.5f�ɐݒ�
				pAvaillableShot->Reload(m_vPosition, 0.5f);

				// �e�𔭎˂����̂ŃN�[���_�E����ݒ�
				m_ShotCoolDown = ShotCoolTime; // ShotCoolTime �� CPlayer.h �Œ�`����Ă��邱�Ƃ��m�F

				// ���ʉ����Đ�
				if (CSoundManager::GetInstance()) 
				{
					CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Shot);
				}
			}
		}
	}

	// ����ɂ��A���˂��ꂽ�e���ړ�����iCShot::Update()���̈ړ����W�b�N�����s�����j
	for (int i = 0; i < ShotMax; ++i)
	{
		if (m_pShot[i] != nullptr) // �|�C���^���L�����m�F����Ȃ����܂��傤
		{
			m_pShot[i]->Update();
		}
	}

	// ���̏������Ȃ��ƁA��x�e�𔭎˂�����N�[���_�E�����i���ɏI��炸�A��x�ƒe�����˂ł��Ȃ��Ȃ�B
	if (m_ShotCoolDown > 0)
	{
		m_ShotCoolDown--;
	}

	//�v���C���[��BSphere�ʒu���X�V.
	UpdateBSpherePos();

	// �e�N���XCCharacter��Update���\�b�h���Ăяo���i�p�����̍X�V�����j
	CCharacter::Update();
}

// �v���C���[����ђe��`�悷�郁�\�b�h�i���t���[���Ăяo�����z��j
void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera)
{
	// �e�N���XCCharacter��Draw���\�b�h���Ăяo���i�v���C���[�{�̂̕`��j
	CCharacter::Draw(View, Proj, Light, Camera);

	//�S�Ă̒e��Draw���\�b�h���Ăяo���A�\����Ԃ̒e�݂̂�`��
	for (int i = 0; i < ShotMax; ++i)
	{
		// �|�C���^���L�����e���\����ԁiCShot::IsDisplay()��true�j�̏ꍇ�̂ݕ`��
		if (m_pShot[i] != nullptr && m_pShot[i]->IsDisplay())
		{
			m_pShot[i]->Draw(View, Proj, Light, Camera);
		}
	}
}

// �v���C���[�ƒe��������Ԃɖ߂����\�b�h�i�Q�[���J�n���⃊�g���C���ȂǂɌĂяo���j
void CPlayer::Init()
{
	for (int i = 0; i < ShotMax; ++i)
	{
		if (m_pShot[i] != nullptr)
		{
			m_pShot[i]->Init();
		}
	}
	m_ShotCoolDown = 0; // �N�[���_�E�������Z�b�g
}

// �g�p����Ă��Ȃ��e�i��\����Ԃ̒e�j��T���ĕԂ��w���p�[�֐�
// ����ɂ��A�ė��p�\�Ȓe�I�u�W�F�N�g���擾�ł���
CShot* CPlayer::UnusedBullet()
{
	for (int i = 0; i < ShotMax; ++i)
	{
		// �|�C���^���L���ŁA���e����\����Ԃł���Ζ��g�p�Ɣ��f
		// CShot::IsDisplay() �� false ��Ԃ��e��T���܂�
		if (m_pShot[i] != nullptr && !m_pShot[i]->IsDisplay())
		{
			return m_pShot[i];
		}
	}
	return nullptr; // ���g�p�̒e���Ȃ��ꍇ��nullptr��Ԃ�
}

CShot& CPlayer::GetShot(int No)
{
	return *m_pShot[No];
}
