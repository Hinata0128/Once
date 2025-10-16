#include "Game.h"
#include "Sound\\SoundManager.h" // SoundManager.h���C���N���[�h
#include "Effect//Effect.h"
#include "StaticMash/StaticMeshManager.h"

//�R���X�g���N�^.
//���������X�g�̓����o�[�ϐ��̏��Ԃł���.
Game::Game( HWND hWnd )
	: m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
	// DirectX �V���O���g���擾
	auto pDx9 = DirectX9::GetInstance();
	auto pDx11 = DirectX11::GetInstance();
	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	StaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);
}


//�f�X�g���N�^.
Game::~Game()
{

}

//�\�z.
void Game::Create()
{
	// DirectX �V���O���g���擾
	auto pDx9 = DirectX9::GetInstance();
	auto pDx11 = DirectX11::GetInstance();

	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	StaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);

	SceneManager::GetInstance()->SetDx9(pDx9);
	SceneManager::GetInstance()->SetDx11(pDx11);

	//Effect�N���X
	//�����ɏ����Ă����Ȃ��Ƃ����Ȃ�
	//GameMain�ɏ����Ă��������ǐ��LoadDate���ǂݍ��܂���܂�.
	Effect::GetInstance()->Create(
		pDx11->GetDevice(),
		pDx11->GetContext());
}

//���[�h�f�[�^�֐�.
HRESULT Game::LoadData()
{
	//�T�E���h�f�[�^�̓ǂݍ���
	if (SoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	//Effect�N���X
	if (FAILED(Effect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	SceneManager::GetInstance()->Create(m_hWnd);
	return S_OK;
}

//����֐�.
void Game::Release()
{
}

//�X�V����.
void Game::Update()
{
	SceneManager::GetInstance()->Update();
}

//�`�揈��.
void Game::Draw()
{
	SceneManager::GetInstance()->Draw();
}

//�Q�[��������/���Z�b�g�p�֐�
void Game::Init()
{
}