#pragma once
#include "GameObject/SkinMeshObject/SkinMeshObject.h"

/************************************************************
*	キャラクタークラス.
**/

class Character
	: public SkinMeshObject
{
public:
	Character();
	virtual ~Character() override;

	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;
protected:
};