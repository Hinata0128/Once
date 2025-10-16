#include "Player.h"
#include "Sound\\SoundManager.h" // �K�v�ł���Ό��ʉ��}�l�[�W���[

// CPlayer�N���X�̃R���X�g���N�^
Player::Player()
	// �R���X�g���N�^���������X�g�ł� m_pShot(0) �͔z��ɂ͕s�v�Ȃ̂ō폜���܂���
{
}

// CPlayer�N���X�̃f�X�g���N�^
Player::~Player()
{
}

// �v���C���[�̏�Ԃ��X�V���郁�\�b�h�i���t���[���Ăяo�����z��j
void Player::Update()
{
	float add_value = 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000) 
	{
		m_vPosition.y += add_value;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) 
	{
		m_vPosition.y -= add_value;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
	{
		m_vPosition.x += add_value;	
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_vPosition.x -= add_value;
	}

	//�v���C���[��BSphere�ʒu���X�V.
	UpdateBSpherePos();

	// �e�N���XCharacter��Update���\�b�h���Ăяo���i�p�����̍X�V�����j
	Character::Update();
}

// �v���C���[����ђe��`�悷�郁�\�b�h�i���t���[���Ăяo�����z��j
void Player::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera)
{
	// �e�N���XCharacter��Draw���\�b�h���Ăяo���i�v���C���[�{�̂̕`��j
	Character::Draw(View, Proj, Light, Camera);

}

// �v���C���[�ƒe��������Ԃɖ߂����\�b�h�i�Q�[���J�n���⃊�g���C���ȂǂɌĂяo���j
void Player::Init()
{
}

