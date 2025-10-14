#pragma once
#include "GameObject\CSpriteObject\Explosion\CExplosion.h"
#include "Sprite3D\CSprite3D.h"
#include <vector>
#include <algorithm>

/****************************************************************
*	爆発マネージャークラス.
**/

class CExplosionManager
{
public:

	~CExplosionManager();

	//スプライトの設定用の初期化.
	void Init(CSprite3D& sprite);

	//爆発の追加.
	void AddExplosion(const D3DXVECTOR3& position);

	void Update();
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj);

	static CExplosionManager* GetInstance()
	{
		//唯一のインスタンスを作成する.
		//※staticで作成されたので2回目以降は、下の1行は無視される.
		static CExplosionManager s_Instance;	//s_:staticの意味.
		return &s_Instance;
	}

	void ExpClear() { m_explosions.clear(); }
private:
	std::vector<CExplosion*> m_explosions;	//爆発エフェクトを格納するコンテナ.
	CSprite3D* m_pSpriteExplosion;			//爆発共通のスプライト.

	CExplosionManager();

	//コピーコンストラクタによるコピーを禁止する.
	CExplosionManager(const CExplosionManager& rhs) = delete;
	//代入演算子によるコピーを禁止する.
	CExplosionManager& operator = (const CExplosionManager& rhs) = delete;
};