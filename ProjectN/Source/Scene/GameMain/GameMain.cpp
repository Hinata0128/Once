#include "GameMain.h"
#include "Sound/SoundManager.h"
#include "Effect//Effect.h"

GameMain::GameMain()
	: CSceneBase			() 
	, m_pStcMeshObj			( std::make_unique<StaticMeshObject>() )

	, m_pGround				( std::make_unique<Ground>() )

	, m_pPlayer				(std::make_unique<Player>())

{
	m_pDx11 = DirectX11::GetInstance();
	m_pDx9	= DirectX9::GetInstance();

	//�J�����̈ʒu��ύX�ł���Ƃ���.
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f); 
	//�J���������Ă���Ƃ����ύX�ł���Ƃ���.
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//���C�g���
	m_Light.vDirection = D3DXVECTOR3(1.5f, 1.f, -1.f);		//���C�g����.
	Initialize();
}

GameMain::~GameMain()
{
	// �O���ō쐬���Ă���̂ŁA�����ł͔j�����Ȃ�
	m_hWnd = nullptr;
	m_pDx11 = nullptr;
	m_pDx9 = nullptr;
}

void GameMain::Initialize()
{

	// �J�����̈ʒu��������
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);
}

void GameMain::Create()
{

}

void GameMain::Update()
{

	//Effect����
	{
		//�G�t�F�N�g�̃C���X�^���X���ƂɕK�v�ȃn���h��
		//���R�\�����Đ��䂷��Ȃ�R�K�v�ɂȂ�
		static ::EsHandle hEffect = -1;

		if (GetAsyncKeyState('Y') & 0x0001) {
			hEffect = Effect::Play(Effect::Test0, D3DXVECTOR3(0.f, 1.f, 0.f));

			//�g��k��
			Effect::SetScale(hEffect, D3DXVECTOR3(0.8f, 0.8f, 0.8f));

			//��](Y����])
			Effect::SetRotation(hEffect, D3DXVECTOR3(0.f, D3DXToRadian(90.0f), 0.f));

			//�ʒu���Đݒ�
			Effect::SetLocation(hEffect, D3DXVECTOR3(0.f, 1.f, 1.f));
		}
		if (GetAsyncKeyState('T') & 0x0001) {
			Effect::Stop(hEffect);
		}
	}
	//�n��.
	m_pGround->Update();

	m_pPlayer->Update();

}

void GameMain::Draw()
{
	Camera();
	Projection();

		//�n�ʕ\��.
	m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
	m_pPlayer->Draw(m_mView, m_mProj, m_Light, m_Camera);
	
	//Effect�N���X
	Effect::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_Camera);
}

HRESULT GameMain::LoadData()
{
	return S_OK;
}

void GameMain::Camera()
{
	D3DXVECTOR3 cam_pos = m_Camera.vPosition;
	D3DXVECTOR3 cam_look = m_Camera.vLook;
	D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//����i�x�N�g���j.

	//�r���[�i�J�����j�ϊ�.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)�r���[�v�Z����.
		&cam_pos, &cam_look, &vUpVec);
}

//�v���W�F�N�V�����֐�.
void GameMain::Projection()
{
	//y�����̎���p�B���l��傫�������王�삪�����Ȃ�.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//���W�A���l.
	//�A�X�y�N�g�i���������j.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;
	float far_z = 100.0f;

	//�v���W�F�N�V�����i�ˉe�j�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,	//(out)�v���W�F�N�V�����v�Z����.
		fov_y,		//����p�iFOV�FField of View�j.
		aspect,		//�A�X�y�N�g.
		near_z,		//�߂��r���[���ʂ�z�l.
		far_z);	//�����r���[���ʂ�z�l.
}

