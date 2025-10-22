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

	//�����[�h�N���X.
	void Reload(const D3DXVECTOR3& pos, float speed);

	//�v���C���[�̈ʒu�Ƀo�E���f�B���O�X�t�B�A�̒��S�𓯊�������.
	void UpdateBPosition();

	//�e�̃o�E���f�B���O�X�t�B�A���擾����.
	std::shared_ptr<BoundingSphere> GetBoundingSphere();

	void SetDisplay(bool disp) { m_Disp = disp; }
	bool IsDisplay() const { return m_Disp; }


private:
	float	m_Speed;	//�X�s�[�h.
	bool	m_Disp;		//�e��\�����邩���Ȃ���.

	std::shared_ptr<BoundingSphere> m_pBSphere;
};