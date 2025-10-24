#pragma once
#include "GameObject/StaticMeshObject/StaticMeshObject.h"
#include "Collision\\BoundingSphere.h"

class StaticMeshManager;

/******************************************************************
*	�V���b�g�N���X.
**/

class PShot
	: public StaticMeshObject
{
public:
	PShot();
	~PShot() override;

	void Update() override;
	void Draw() override;

	//�e�̏�����.
	void Init();

	//�����[�h.
	void Reload(const D3DXVECTOR3& pos, const D3DXVECTOR3& direction, float speed);

	//�v���C���[�̈ʒu�Ƀo�E���f�B���O�X�t�B�A�̒��S�𓯊�������.
	void UpdateBPosition();

	//�e�̃o�E���f�B���O�X�t�B�A���擾����.
	std::shared_ptr<BoundingSphere> GetBoundingSphere();

	void SetDisplay(bool disp) { m_Disp = disp; }
	bool IsDisplay() const { return m_Disp; }

	//Player�̒e���������Ă��邩��Manager�ɂ킽��.
	bool IsActive() const;


private:
	D3DXVECTOR3 m_Direction;

	float	m_Speed;	//�X�s�[�h.
	bool	m_Disp;		//�e��\�����邩���Ȃ���.
	bool	m_IsActive;	//�e���������Ă��邩?

	std::shared_ptr<BoundingSphere> m_pBSphere;
};