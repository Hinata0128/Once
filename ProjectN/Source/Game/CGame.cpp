#include "CGame.h"
#include "Sound\\CSoundManager.h" // CSoundManager.h���C���N���[�h
#include "Effect//Effect.h"
#include "StaticMash/CStaticMeshManager.h"

//�R���X�g���N�^.
//���������X�g�̓����o�[�ϐ��̏��Ԃł���.
CGame::CGame(CDirectX9& pDx9, CDirectX11& pDx11, HWND hWnd)
	: m_pDx9				(&pDx9)
	, m_pDx11				(&pDx11)
	, m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	CStaticMeshManager::GetInstance()->Create(pDx9, pDx11);
}


//�f�X�g���N�^.
CGame::~CGame()
{

}

//�\�z.
void CGame::Create()
{
	//�X�^�e�B�b�N���b�V���}�l�[�W���[�̍\�z
	CStaticMeshManager::GetInstance()->Create(*m_pDx9, *m_pDx11);

	CSceneManager::GetInstance()->SetDx11(m_pDx11);
	CSceneManager::GetInstance()->SetDx9(m_pDx9);

	//Effect�N���X
	//�����ɏ����Ă����Ȃ��Ƃ����Ȃ�
	//GameMain�ɏ����Ă��������ǐ��LoadDate���ǂݍ��܂���܂�.
	Effect::GetInstance()->Create(
		m_pDx11->GetDevice(),
		m_pDx11->GetContext());
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
	CSceneManager::GetInstance()->Drae();
}

//�Q�[��������/���Z�b�g�p�֐�
void CGame::Init()
{
}