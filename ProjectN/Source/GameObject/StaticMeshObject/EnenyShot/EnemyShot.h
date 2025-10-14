#pragma once
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"
#include "StaticMash/CStaticMeshManager.h"

//----------------------------------------
// 前方宣言.
//----------------------------------------
class CPlayer;

/*********************************************************************
*	ホーミング弾クラス.
**/

class EnemyShot
	: public CStaticMeshObject
{
public:
	EnemyShot();
	~EnemyShot() override;

	//ホーミング弾独自の初期化関数を作成.
	void Init(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer);
	
	void Update() override;
	void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera ) override;

	bool IsActive() const { return m_bIsActive; }
	// アクティブ状態を設定 (マネージャーが弾を「使用済み」にする際などに使用)
	void SetActive(bool active) { m_bIsActive = active; }

	//衝突判定用.
	D3DXVECTOR3 GetPosition() const { return m_vposition; } // 必要に応じて、CStaticMeshObjectから取得できるなら不要

private:
	D3DXVECTOR3 m_vposition;       // 弾の現在位置 (CStaticMeshObjectが内部で持っているかもしれませんが、ホーミング計算用に保持)
	D3DXVECTOR3 m_velocity;        // 弾の現在の速度ベクトル (方向と速さ)
	float       m_speed;           // 弾の移動速度
	float       m_homingStrength;  // ホーミングの強さ (0.0～1.0、高いほど急カーブ)
	float       m_lifeTime;        // 弾の寿命（秒）
	float       m_elapsedTime;     // 弾が生成されてからの経過時間

	CPlayer*	m_pTargetPlayer;   // 追尾対象となるプレイヤーへのポインタ

	bool		m_bIsActive;       // 弾が現在アクティブ（生存）しているかどうかのフラグ
};