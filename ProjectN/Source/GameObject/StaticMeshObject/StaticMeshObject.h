#pragma once

#include "GameObject\\GameObject.h"
#include "StaticMash\StaticMesh.h"
#include "Collision\BoundingSphere.h"

/************************************************************
*	スタティックメッシュオブジェクトクラス.
*	3DSTGではメインの分類.
**/
class StaticMeshObject
	: public GameObject
{
public:
	StaticMeshObject();
	virtual ~StaticMeshObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//メッシュを接続する.
	void AttachMesh(StaticMesh& pMesh ){
		m_pMesh = &pMesh;
	}
	//スプライトを切り離す.
	void DetachMesh(){
		m_pMesh = nullptr;
	}

	//バウンディングスフィア取得.
	BoundingSphere* GetBSphere() const
	{
		return m_pBSphere;
	}
	//短くかける関数.
	//モデルに合わせたバウンディングスフィア作成のラッパー関数.
	HRESULT CreateBSphereForMesh(const StaticMesh& pMesh)
	{
		return m_pBSphere->CreateSphereForMesh(pMesh);
	}
	//バウンディングスフィアをオブジェクト位置に合わせる.
	//※モデルの原点が中心の場合を提示.
	void UpdateBSpherePos()
	{
		m_pBSphere->SetPosition(m_vPosition);
	}

protected:
	StaticMesh*		m_pMesh;
	BoundingSphere*	m_pBSphere;
};
