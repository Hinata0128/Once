#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"
#include "Collision\CBoundingSphere.h" // CBSphere�̎g�p�̂���

/**************************************************
*	�e�׽.
**/
class CShot
	: public CStaticMeshObject
{
public:
	CShot();
	virtual ~CShot();

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& light, CAMERA& camera) override;

	
	void SetDisplay(bool disp) { m_Disp = disp; }
	bool IsDisplay() const { return m_Disp; } 

	//�e���Đݒ�.
	void Reload(const D3DXVECTOR3& Pos, float speed = 2.0f); // speed������ǉ����A�f�t�H���g�l��ݒ�

	void Init(); // �e��������Ԃɖ߂�

	//���g�̈ʒu�Ƀo�E���f�B���O�X�t�B�A�̒��S�𓯊�������
	void UpdateBoundingSpherePosition();

	//�e�̃o�E���f�B���O�X�t�B�A�ւ̃|�C���^���擾����
	CBoundingSphere* GetBoundingSphere() { return m_pBSphere; }

protected:

	bool	m_Disp;		//�\���ؑ�.
	float	m_speed;	//�X�s�[�h.

};