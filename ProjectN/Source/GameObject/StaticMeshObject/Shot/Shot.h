#pragma once
#include "GameObject/StaticMeshObject/StaticMeshObject.h"

class StaticMeshManager;

/******************************************************************
*	�V���b�g�N���X.
**/

class Shot
	: public StaticMeshObject
{
public:
	Shot();
	~Shot() override;

	void Update() override;
	void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	//�e�̏�����.
	void Init();

	//�����[�h�N���X.
	void Reload(const D3DXVECTOR3& pos, float speed);


private:
	float m_Speed;	//�X�s�[�h.
};