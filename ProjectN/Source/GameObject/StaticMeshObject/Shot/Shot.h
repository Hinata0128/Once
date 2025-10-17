#pragma once
#include "GameObject/StaticMeshObject/StaticMeshObject.h"

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

private:

};