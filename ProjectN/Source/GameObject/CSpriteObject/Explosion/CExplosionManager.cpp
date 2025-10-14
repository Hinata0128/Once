#include "CExplosionManager.h"
#include "Sound/CSoundManager.h"

//privateコンストラクタ実装.
CExplosionManager::CExplosionManager()
	: m_pSpriteExplosion		(nullptr)
{
	m_explosions.clear();
}

CExplosionManager::~CExplosionManager()
{
	//コンテナ内の全ての爆発オブジェクトを解放.
	for (CExplosion* exp : m_explosions)
	{
		SAFE_DELETE(exp);
	}
	m_explosions.clear();
}

void CExplosionManager::Init(CSprite3D& sprite)
{
	m_pSpriteExplosion = &sprite;	//渡されたスプライトの参照をポインタで保持.
}

//新しい爆発エフェクトを追加する.
void CExplosionManager::AddExplosion(const D3DXVECTOR3& position)
{
	if (!m_pSpriteExplosion)
	{
		return;
	}
	CExplosion* newExplosion = new CExplosion();	//新しいCExplosionオブジェクトを作成.
	newExplosion->AttachSprite(*m_pSpriteExplosion);//共通のスプライトをアタッチ.
	newExplosion->SetPosition(position);			//爆発の発生位置を設定.
	newExplosion->ResetAnimation();					//アニメーションを最初から再生するようにリセット/
	m_explosions.push_back(newExplosion);			//ベクトルに新しい爆発を追加.
}

void CExplosionManager::Update()
{
	//現在表示中の全ての爆発エフェクトを更新.
	for (CExplosion* exp : m_explosions)
	{
		exp->Update();
	}

	//ラムダ式.
	std::erase_if(m_explosions, [](CExplosion* exp)
	{
		if (exp->IsFinished())
		{
			SAFE_DELETE(exp);
			return true;
		}
		return false;
	});
}

void CExplosionManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj)
{
	for (int i = 0; i < m_explosions.size(); ++i)
	{
		//爆発が現在表示状態である場合のみ描画します.
		if (m_explosions[i]->IsDisplay())
		{
			m_explosions[i]->Draw(View, Proj);	//各爆発の描画処理を呼び出す.
		}
	}
}
