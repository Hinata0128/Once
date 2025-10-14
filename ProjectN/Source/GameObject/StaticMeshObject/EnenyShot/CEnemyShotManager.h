#pragma once
#include <vector>
#include "GameObject/StaticMeshObject/EnenyShot/EnemyShot.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"

/*****************************************************************
*	ホーミング弾マネージャー.
**/

class CEnemyShotManager
{
public:

	~CEnemyShotManager();
	//シングルトンインスタンスを取得する静的メソッド.
	static CEnemyShotManager* GetInstance();

	void Update();

	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera);

	//新しいホーミング弾を作成し、管理リストに追加する.
	void AddHomingShot(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer);

	//全てのホーミング弾をリストから削除し、メモリを解放する.
	void ClearAllHomingShot();

	void RemoveShot(size_t index);

	void Init();


	const std::vector<EnemyShot*>& GetHomingShots() const { return m_homingShots; }

	EnemyShot* GetShot(size_t No)
	{
		if (No < m_homingShots.size())
		{
			return m_homingShots[No];
		}
		return nullptr;
	}

	//ホーミング弾の数を取得する関数
	size_t GetShotCount() const { return m_homingShots.size(); }

private:
	//外部からコンストラクタへのアクセスを禁止する.
	CEnemyShotManager();
	//コピーコンストラクタによるコピーを禁止する.
	//「=delete」で関数の定義を削除できる.
	CEnemyShotManager(const CEnemyShotManager& rhs) = delete;
	//代入演算子によるコピーを禁止する.
	//operator(オペレータ):演算子のオーバーロードで、演算の中身を拡張できる.
	CEnemyShotManager& operator = (const CEnemyShotManager& rhs) = delete;
private:
	static CEnemyShotManager* m_pInstance;	//シングルトンインスタンス.

	//現在アクティブなホーミング弾を保持するコンテナ.
	std::vector<EnemyShot*> m_homingShots;

};
