#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/SpriteObject/SpriteObject.h"
#include "SceneManager/SceneManager.h"

#include "GameObject/StaticMeshObject/Ground/Ground.h"
#include "GameObject/StaticMeshObject/Character/Player/Player.h"
#include "DebugText/DebugText.h"
#include "GameObject/StaticMeshObject/Character/Character.h"


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

	Sprite3D*			m_pSpriteGround;
	Sprite3D*			m_pSpriteExplosion;

	//スタティックメッシュ(使いまわす資源)
	StaticMesh*		m_pStaticMeshFighter;	//自機.
	StaticMesh*		m_pStaticMeshGround;	//地面.
	StaticMesh*		m_pStaticMeshEnemyA;	//敵A.
	StaticMesh*		m_pStaticMeshEnemyB;	//敵B.
	StaticMesh*		m_pStaticMeshBullet;	//弾.
	StaticMesh*		m_pStaticMeshBSohere;	//バウンディングスフィア(当たり判定用).


	StaticMesh*		m_pGameMain;
	Sprite2D*			m_pSpriteTitle;

	//スタティックメッシュオブジェクトクラス.
	StaticMeshObject* m_pStcMeshObj;


	//キャラクタークラス
	Character*			m_pPlayer;

	//地面クラス.
	Ground*			m_pGround;
	DebugText*			m_pDbgText;	//デバックテキスト.

};