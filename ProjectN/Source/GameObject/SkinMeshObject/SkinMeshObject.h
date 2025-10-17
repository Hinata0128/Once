#pragma once

#include "GameObject/GameObject.h"
#include "SkinMesh/SkinMesh.h"

/************************************************************
*	�X�L�����b�V���I�u�W�F�N�g�N���X.
**/
class SkinMeshObject
	: public GameObject
{
public:
	SkinMeshObject();
	virtual ~SkinMeshObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	//���b�V����ڑ�����.
	void AttachMesh(SkinMesh& pMesh);
	//���b�V����؂藣��.
	void DetachMesh();


protected:
	SkinMesh*					m_pMesh;
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	//�A�j���[�V�����R���g���[��
};
