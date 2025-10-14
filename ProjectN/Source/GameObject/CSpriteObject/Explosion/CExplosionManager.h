#pragma once
#include "GameObject\CSpriteObject\Explosion\CExplosion.h"
#include "Sprite3D\CSprite3D.h"
#include <vector>
#include <algorithm>

/****************************************************************
*	�����}�l�[�W���[�N���X.
**/

class CExplosionManager
{
public:

	~CExplosionManager();

	//�X�v���C�g�̐ݒ�p�̏�����.
	void Init(CSprite3D& sprite);

	//�����̒ǉ�.
	void AddExplosion(const D3DXVECTOR3& position);

	void Update();
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj);

	static CExplosionManager* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static CExplosionManager s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}

	void ExpClear() { m_explosions.clear(); }
private:
	std::vector<CExplosion*> m_explosions;	//�����G�t�F�N�g���i�[����R���e�i.
	CSprite3D* m_pSpriteExplosion;			//�������ʂ̃X�v���C�g.

	CExplosionManager();

	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	CExplosionManager(const CExplosionManager& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	CExplosionManager& operator = (const CExplosionManager& rhs) = delete;
};