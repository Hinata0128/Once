#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

#include "GameObject/StaticMeshObject/Ground/Ground.h"


/*********************************************
*	ゲームメイン画像クラス.
**/

class GameMain
	: public CSceneBase
{
public:
	GameMain();
	~GameMain() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

	HRESULT LoadData();

	//カメラ関数.
	void Camera();
	//プロジェクション関数.
	void Projection();

private:
	//ゲームで扱うスプライトデータ(使いまわす資源).
	Sprite3D*			m_pSp3D;

	//スタティックメッシュ(使いまわす資源)
	StaticMesh*		m_pStaticMeshGround;	//地面.

	//スタティックメッシュオブジェクトクラス.
	StaticMeshObject* m_pStcMeshObj;

	//地面クラス.
	Ground*			m_pGround;

};