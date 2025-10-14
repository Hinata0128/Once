#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"
#include "StaticMash/CStaticMeshManager.h"

//----------------------------------------
// �O���錾.
//----------------------------------------
class CPlayer;

/*********************************************************************
*	�z�[�~���O�e�N���X.
**/

class EnemyShot
	: public CStaticMeshObject
{
public:
	EnemyShot();
	~EnemyShot() override;

	//�z�[�~���O�e�Ǝ��̏������֐����쐬.
	void Init(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer);
	
	void Update() override;
	void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	bool IsActive() const { return m_bIsActive; }
	// �A�N�e�B�u��Ԃ�ݒ� (�}�l�[�W���[���e���u�g�p�ς݁v�ɂ���ۂȂǂɎg�p)
	void SetActive(bool active) { m_bIsActive = active; }

	//�Փ˔���p.
	D3DXVECTOR3 GetPosition() const { return m_vposition; } // �K�v�ɉ����āACStaticMeshObject����擾�ł���Ȃ�s�v

private:
	D3DXVECTOR3 m_vposition;       // �e�̌��݈ʒu (CStaticMeshObject�������Ŏ����Ă��邩������܂��񂪁A�z�[�~���O�v�Z�p�ɕێ�)
	D3DXVECTOR3 m_velocity;        // �e�̌��݂̑��x�x�N�g�� (�����Ƒ���)
	float       m_speed;           // �e�̈ړ����x
	float       m_homingStrength;  // �z�[�~���O�̋��� (0.0�`1.0�A�����قǋ}�J�[�u)
	float       m_lifeTime;        // �e�̎����i�b�j
	float       m_elapsedTime;     // �e����������Ă���̌o�ߎ���

	CPlayer*	m_pTargetPlayer;   // �ǔ��ΏۂƂȂ�v���C���[�ւ̃|�C���^

	bool		m_bIsActive;       // �e�����݃A�N�e�B�u�i�����j���Ă��邩�ǂ����̃t���O
};