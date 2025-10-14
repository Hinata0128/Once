#include "CExplosionManager.h"
#include "Sound/CSoundManager.h"

//private�R���X�g���N�^����.
CExplosionManager::CExplosionManager()
	: m_pSpriteExplosion		(nullptr)
{
	m_explosions.clear();
}

CExplosionManager::~CExplosionManager()
{
	//�R���e�i���̑S�Ă̔����I�u�W�F�N�g�����.
	for (CExplosion* exp : m_explosions)
	{
		SAFE_DELETE(exp);
	}
	m_explosions.clear();
}

void CExplosionManager::Init(CSprite3D& sprite)
{
	m_pSpriteExplosion = &sprite;	//�n���ꂽ�X�v���C�g�̎Q�Ƃ��|�C���^�ŕێ�.
}

//�V���������G�t�F�N�g��ǉ�����.
void CExplosionManager::AddExplosion(const D3DXVECTOR3& position)
{
	if (!m_pSpriteExplosion)
	{
		return;
	}
	CExplosion* newExplosion = new CExplosion();	//�V����CExplosion�I�u�W�F�N�g���쐬.
	newExplosion->AttachSprite(*m_pSpriteExplosion);//���ʂ̃X�v���C�g���A�^�b�`.
	newExplosion->SetPosition(position);			//�����̔����ʒu��ݒ�.
	newExplosion->ResetAnimation();					//�A�j���[�V�������ŏ�����Đ�����悤�Ƀ��Z�b�g/
	m_explosions.push_back(newExplosion);			//�x�N�g���ɐV����������ǉ�.
}

void CExplosionManager::Update()
{
	//���ݕ\�����̑S�Ă̔����G�t�F�N�g���X�V.
	for (CExplosion* exp : m_explosions)
	{
		exp->Update();
	}

	//�����_��.
	std::erase_if(m_explosions, [](CExplosion* exp)
	{
		if (exp->IsFinished())
		{
			SAFE_DELETE(exp);
			return true;
		}
		return false;
	});
}

void CExplosionManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj)
{
	for (int i = 0; i < m_explosions.size(); ++i)
	{
		//���������ݕ\����Ԃł���ꍇ�̂ݕ`�悵�܂�.
		if (m_explosions[i]->IsDisplay())
		{
			m_explosions[i]->Draw(View, Proj);	//�e�����̕`�揈�����Ăяo��.
		}
	}
}
