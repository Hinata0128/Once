#pragma once

#include "GameObject/GameObject.h"
#include "SkinMesh/SkinMesh.h"

/************************************************************
*	スキンメッシュオブジェクトクラス.
**/
class SkinMeshObject
	: public GameObject
{
public:
	SkinMeshObject();
	virtual ~SkinMeshObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	//メッシュを接続する.
	void AttachMesh(SkinMesh& pMesh);
	//メッシュを切り離す.
	void DetachMesh();

public:
	//セット・ゲット関数.
	//アニメーションの再生用セット関数.
	void SetIsLoop(const bool& IsLoop);



protected:
	SkinMesh*					m_pMesh;
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	//アニメーションコントローラ
	bool						m_Loop;	//アニメーションのループ再生.
};
