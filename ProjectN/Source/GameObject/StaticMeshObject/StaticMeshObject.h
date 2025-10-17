#pragma once

#include "GameObject\\GameObject.h"
#include "StaticMash\StaticMesh.h"


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
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	//���b�V����ڑ�����.
	void AttachMesh(StaticMesh& pMesh ){
		m_pMesh = &pMesh;
	}
	//�X�v���C�g��؂藣��.
	void DetachMesh(){
		m_pMesh = nullptr;
	}


protected:
	StaticMesh*		m_pMesh;
};
