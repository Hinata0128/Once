#pragma once
#include "GameObject\StaticMeshObject\Character\Character.h"

/**************************************************
*	�v���C���[�N���X.
**/

class Player
	: public Character	//�L�����N�^�[�N���X���p��.
{
public:
	Player();
	virtual ~Player() override;

	virtual void Update() override;
	virtual void Draw( 
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	const D3DXVECTOR3& GetPosition() const { return m_vPosition; }

	// �v���C���[�̏���������
	void Init();	
protected:
};