#include "CGame.h"
#include "Sound\\CSoundManager.h" // CSoundManager.h���C���N���[�h
#include "Effect//Effect.h"
#include "StaticMash/CStaticMeshManager.h"

//�R���X�g���N�^.
//���������X�g�̓����o�[�ϐ��̏��Ԃł���.
CGame::CGame( HWND hWnd )
	: m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
	// DirectX �V���O���g���擾
	auto pDx9 = CDirectX9::GetInstance();
	auto pDx11 = CDirectX11::GetInstance();
	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	CStaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);
}


//�f�X�g���N�^.
CGame::~CGame()
{

}

//�\�z.
void CGame::Create()
{
	// DirectX �V���O���g���擾
	auto pDx9 = CDirectX9::GetInstance();
	auto pDx11 = CDirectX11::GetInstance();

	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	CStaticMeshManager::GetInstance()->Create(*pDx9, *pDx11);

	CSceneManager::GetInstance()->SetDx9(pDx9);
	CSceneManager::GetInstance()->SetDx11(pDx11);

	//Effect�N���X
	//�����ɏ����Ă����Ȃ��Ƃ����Ȃ�
	//GameMain�ɏ����Ă��������ǐ��LoadDate���ǂݍ��܂���܂�.
	Effect::GetInstance()->Create(
		pDx11->GetDevice(),
		pDx11->GetContext());
}

//���[�h�f�[�^�֐�.
HRESULT CGame::LoadData()
{
	//�T�E���h�f�[�^�̓ǂݍ���
	if (CSoundManager::GetInstance()->Load(m_hWnd) == false) {
		return E_FAIL;
	}

	//Effect�N���X
	if (FAILED(Effect::GetInstance()->LoadData()))
	{
		return E_FAIL;
	}


	CSceneManager::GetInstance()->Create(m_hWnd);
	return S_OK;
}

//����֐�.
void CGame::Release()
{
}

//�X�V����.
void CGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

//�`�揈��.
void CGame::Draw()
{
	CSceneManager::GetInstance()->Draw();
}

//�Q�[��������/���Z�b�g�p�֐�
void CGame::Init()
{
}