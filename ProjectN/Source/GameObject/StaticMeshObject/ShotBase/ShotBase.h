#pragma once
#include "GameObject//StaticMeshObject//ShotBase//ShotBase.h"

#include "GameObject//StaticMeshObject//StaticMeshObject.h"
#include "Collision//BoundingSphere.h"


/************************************************************
*	�e�̃x�[�X�N���X.
**/

class ShotBase
	: public StaticMeshObject
{
public:
	ShotBase();
	virtual ~ShotBase() override;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Init();

	// �e�̍Đݒ�i�ʒu�E�����E�X�s�[�h�j
	virtual void Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed) = 0;

	// �o�E���f�B���O�X�t�B�A���ʒu�ɓ���
	virtual void UpdateBPosition();

	// �o�E���f�B���O�X�t�B�A���擾
	virtual std::shared_ptr<BoundingSphere> GetBoundingSphere();

	// �\���t���O�ݒ�
	virtual void SetDisplay(bool disp) { m_Disp = disp; }

	// �\���t���O�擾
	virtual bool IsDisplay() const { return m_Disp; }

	// �A�N�e�B�u��Ԏ擾
	virtual bool IsActive() const { return m_IsActive; }
protected:
	//�q�N���X�ɕK�v�ɂȂ郁���o�[�ϐ��������ɏ����Ă���.
	D3DXVECTOR3 m_Direction;

	float		m_Speed;	//�X�s�[�h.
	bool		m_Disp;		//�e��\�����邩���Ȃ���.
	bool		m_IsActive;	//�e���������Ă��邩?

	std::shared_ptr<BoundingSphere> m_BSphere;
};