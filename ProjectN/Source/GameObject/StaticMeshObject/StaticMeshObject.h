#pragma once

#include "GameObject\\GameObject.h"
#include "StaticMash\StaticMesh.h"
#include "Collision\BoundingSphere.h"

/************************************************************
*	�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
*	3DSTG�ł̓��C���̕���.
**/
class StaticMeshObject
	: public GameObject
{
public:
	StaticMeshObject();
	virtual ~StaticMeshObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//���b�V����ڑ�����.
	void AttachMesh(StaticMesh& pMesh ){
		m_pMesh = &pMesh;
	}
	//�X�v���C�g��؂藣��.
	void DetachMesh(){
		m_pMesh = nullptr;
	}

	//�o�E���f�B���O�X�t�B�A�擾.
	BoundingSphere* GetBSphere() const
	{
		return m_pBSphere;
	}
	//�Z��������֐�.
	//���f���ɍ��킹���o�E���f�B���O�X�t�B�A�쐬�̃��b�p�[�֐�.
	HRESULT CreateBSphereForMesh(const StaticMesh& pMesh)
	{
		return m_pBSphere->CreateSphereForMesh(pMesh);
	}
	//�o�E���f�B���O�X�t�B�A���I�u�W�F�N�g�ʒu�ɍ��킹��.
	//�����f���̌��_�����S�̏ꍇ���.
	void UpdateBSpherePos()
	{
		m_pBSphere->SetPosition(m_vPosition);
	}

protected:
	StaticMesh*		m_pMesh;
	BoundingSphere*	m_pBSphere;
};
