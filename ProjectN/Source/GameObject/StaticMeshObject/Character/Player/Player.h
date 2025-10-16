#pragma once
#include "GameObject\StaticMeshObject\Character\Character.h"

/**************************************************
*	プレイヤークラス.
**/

class Player
	: public Character	//キャラクタークラスを継承.
{
public:
	Player();
	virtual ~Player() override;

	virtual void Update() override;
	virtual void Draw( 
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	const D3DXVECTOR3& GetPosition() const { return m_vPosition; }

	// プレイヤーの初期化処理
	void Init();	
protected:
};