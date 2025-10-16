#include "CGameMain.h"
#include "Sound/CSoundManager.h"
#include "Effect//Effect.h"

CGameMain::CGameMain()
	: CSceneBase			() 
	, m_pDbgText			( nullptr )
	, m_pSpriteGround		( nullptr )
	, m_pSpriteExplosion	( nullptr )

	, m_pStaticMeshFighter	( nullptr )
	, m_pStaticMeshGround	( nullptr )
	, m_pStaticMeshEnemyA	( nullptr )
	, m_pStaticMeshEnemyB	( nullptr )
	, m_pStaticMeshBullet	( nullptr )
	, m_pStaticMeshBSohere	( nullptr )

	, m_pStcMeshObj			( nullptr )
	, m_pPlayer				( nullptr )

	, m_pGround				( nullptr )

	, m_pGameMain			( nullptr )
	, m_pSpriteTitle		( nullptr )
{
	m_pDx11 = CDirectX11::GetInstance();
	m_pDx9	= CDirectX9::GetInstance();

	//�J�����̈ʒu��ύX�ł���Ƃ���.
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f); 
	//�J���������Ă���Ƃ����ύX�ł���Ƃ���.
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//���C�g���
	m_Light.vDirection = D3DXVECTOR3(1.5f, 1.f, -1.f);		//���C�g����.
	Initialize();
}

CGameMain::~CGameMain()
{
	//�n�ʂ̔j��.
	SAFE_DELETE(m_pGround);

	//�v���C���[�̔j��.
	SAFE_DELETE(m_pPlayer);
	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X�̔j��.
	SAFE_DELETE(m_pStcMeshObj);

	SAFE_DELETE(m_pStaticMeshBSohere);
	SAFE_DELETE(m_pStaticMeshBullet);
	SAFE_DELETE(m_pStaticMeshEnemyB);
	SAFE_DELETE(m_pStaticMeshEnemyA);
	SAFE_DELETE(m_pStaticMeshGround);
	SAFE_DELETE(m_pStaticMeshFighter);


	//�����X�v���C�g��� (�����CGame�Ő����������̂Ȃ̂Ŏc��)
	SAFE_DELETE(m_pSpriteExplosion);
	//�n�ʃX�v���C�g�̉��.
	SAFE_DELETE(m_pSpriteGround);

	//�f�o�b�N�e�L�X�g�̔j��.
	SAFE_DELETE(m_pDbgText);

	// �O���ō쐬���Ă���̂ŁA�����ł͔j�����Ȃ�
	m_hWnd = nullptr;
	m_pDx11 = nullptr;
	m_pDx9 = nullptr;
}

void CGameMain::Initialize()
{

	// �J�����̈ʒu��������
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	m_Score = 0;
	m_Count = 0;

	m_isGameOverTransitioning = false;
	m_gameOverDelayTimer	= 0;
	m_isEndingTransitioning = false;
	m_endingDelayTimer		= 0;
}

void CGameMain::Create()
{


	//�f�o�b�N�e�L�X�g�̃C���X�^���X����.
	m_pDbgText = new CDebugText();



	//�X�^�e�B�b�N���b�V���̃C���X�^���X����.
	m_pStaticMeshFighter	= new CStaticMesh();
	m_pStaticMeshGround		= new CStaticMesh();
	m_pStaticMeshEnemyA		= new CStaticMesh();
	m_pStaticMeshEnemyB		= new CStaticMesh();
	m_pStaticMeshBullet		= new CStaticMesh();
	m_pStaticMeshBSohere	= new CStaticMesh(); // BSphere�p�̃��b�V���C���X�^���X�������Ő���

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X�̃C���X�^���X����.
	m_pStcMeshObj = new CStaticMeshObject();

	//�X�v���C�g�̃C���X�^���X�쐬.
	m_pSpriteGround		= new CSprite3D();
	m_pSpriteExplosion	= new CSprite3D(); // �����}�l�[�W���[�ɓn�����߂̃X�v���C�g

	//�n�ʃX�v���C�g�̍\����
	CSprite3D::SPRITE_STATE SSGround;
	SSGround.Disp.w = 1.f;
	SSGround.Disp.h = 1.f;
	SSGround.Base.w = 256.f;
	SSGround.Base.h = 256.f;
	SSGround.Stride.w = 256.f;
	SSGround.Stride.h = 256.f;

	//�n�ʃX�v���C�g�̓ǂݍ���.
	m_pSpriteGround->Init(*m_pDx11,
		_T("Data\\Texture\\Ground.png"), SSGround);


	// �����X�v���C�g�̍\����
	CSprite3D::SPRITE_STATE SSExplosion =
	{ 1.f, 1.f,			// Disp(w.h)
		256.f, 256.f ,	// Base(w.h)
		32.f , 32.f		// Stride(w.h)
	};
	//�����X�v���C�g�̓ǂݍ���.
	m_pSpriteExplosion->Init(*m_pDx11,
		_T("Data\\Texture\\explosion.png"), SSExplosion);


	//�L�����N�^�[�N���X�̃C���X�^���X����.
	m_pPlayer = new CPlayer();

	//�n�ʃN���X�̃C���X�^���X����.
	m_pGround = new CGround();

	//�f�o�b�N�e�L�X�g�̓ǂݍ���.
	if (FAILED(m_pDbgText->Init(*m_pDx11)))
	{
		return ;
	}





	//�X�^�e�B�b�N���b�V���̓ǂݍ���.
	m_pStaticMeshFighter->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Fighter\\Fighter.x"));
	//�n�ʂ̓ǂݍ���.
	m_pStaticMeshGround->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Ground\\ground.x"));
	//�o�E���f�B���O�X�t�B�A(�����蔻��p).
	m_pStaticMeshBSohere->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Collision\\Sphere.x"));

	//�X�^�e�B�b�N���b�V����ݒ�.
	m_pStcMeshObj->AttachMesh(*m_pStaticMeshFighter);
	//�v���C���[��ݒ�.
	m_pPlayer->AttachMesh(*m_pStaticMeshFighter);
	//�n�ʃX�v���C�g��ݒ�.
	m_pGround->AttachMesh(*m_pStaticMeshGround);

	//�o�E���f�B���O�X�t�B�A�̍쐬.
	m_pPlayer->CreateBSphereForMesh(*m_pStaticMeshBSohere);



	//�L�����N�^�[�̏������W������.
	m_pPlayer->SetPosition(0.f, 1.f, 6.f);
}

void CGameMain::Update()
{

	constexpr int POINT = 100;
	constexpr int GameClreaPoint = 1500;

	m_Count++;



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
	//�v���C���[.
	m_pPlayer->Update();



}

void CGameMain::Draw()
{
	Camera();
	Projection();

		//�n�ʕ\��.
	m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
	//�v���C���[�\��.
	m_pPlayer->Draw(m_mView, m_mProj, m_Light, m_Camera);
	
	//Effect�N���X
	Effect::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_Camera);
	

	//������SetDepth(false)�̉���true�����Ȃ��Ɠ����ɂȂ�.
	//�[�x�e�X�g�����ɂ��邱�ƂŁA�������Ԃŕ`�悳���邱�Ƃ��ł���.
	m_pDx11->SetDepth(false);
	//��肽�����Ƃ��I�������̂ŁA�[�x�e�X�g��L���ɂ��Ă���.
	m_pDx11->SetDepth(true);

	


	if (m_pDbgText)

	{

		m_pDbgText->SetColor(1.0f, 1.0f, 1.0f);

		TCHAR dbgText[64];

		_stprintf_s(dbgText, _T("Score: %d"), m_Score);

		m_pDbgText->Render(dbgText, 600, 10);

	}
}

HRESULT CGameMain::LoadData()
{
	return S_OK;
}

void CGameMain::Camera()
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
void CGameMain::Projection()
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

