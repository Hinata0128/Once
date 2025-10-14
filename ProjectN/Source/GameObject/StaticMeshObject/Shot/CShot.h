#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"
#include "Collision\CBoundingSphere.h" // CBSphereの使用のため

/**************************************************
*	弾ｸﾗｽ.
**/
class CShot
	: public CStaticMeshObject
{
public:
	CShot();
	virtual ~CShot();

	virtual void Update() override;
	virtual void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& light, CAMERA& camera) override;

	
	void SetDisplay(bool disp) { m_Disp = disp; }
	bool IsDisplay() const { return m_Disp; } 

	//弾を再設定.
	void Reload(const D3DXVECTOR3& Pos, float speed = 2.0f); // speed引数を追加し、デフォルト値を設定

	void Init(); // 弾を初期状態に戻す

	//自身の位置にバウンディングスフィアの中心を同期させる
	void UpdateBoundingSpherePosition();

	//弾のバウンディングスフィアへのポインタを取得する
	CBoundingSphere* GetBoundingSphere() { return m_pBSphere; }

protected:

	bool	m_Disp;		//表示切替.
	float	m_speed;	//スピード.

};