#include "CPlayer.h"
#include "Sound\\CSoundManager.h" // 必要であれば効果音マネージャー

// CPlayerクラスのコンストラクタ
CPlayer::CPlayer()
	: m_ShotCoolDown(0) // クールダウンカウンターを初期化
	// コンストラクタ初期化リストでの m_pShot(0) は配列には不要なので削除しました
{
	// ShotMax個のCShotオブジェクトを動的に生成し、ポインタ配列に格納
	// CPlayer.h で ShotMax が定義されていることを確認してください (例: const int ShotMax = 10;)
	for (int i = 0; i < ShotMax; ++i)
	{
		m_pShot[i] = new CShot();
	}
}

// CPlayerクラスのデストラクタ
CPlayer::~CPlayer()
{
	//メモリリークを防ぐため、newしたCShotオブジェクトを解放
	for (int i = 0; i < ShotMax; ++i)
	{
		if (m_pShot[i] != nullptr) // nullptrチェックは安全のため
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr; // 解放後、ポインタをnullptrに設定
		}
	}
}

// プレイヤーの状態を更新するメソッド（毎フレーム呼び出される想定）
void CPlayer::Update()
{
	float add_value = 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000) {

		if (m_vPosition.y <= WallUP)
		{
			m_vPosition.y += add_value;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (m_vPosition.y >= WallDOWN)
		{
			m_vPosition.y -= add_value;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (m_vPosition.x <= WallRIGHT)
		{
			m_vPosition.x += add_value;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (m_vPosition.x >= WallLEFT)
		{
			m_vPosition.x -= add_value;
		}
	}

	// 'Z'キーが押された時の弾の発射処理
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		// クールダウンが終了している場合（クールダウンカウンターが0以下）のみ発射を試みる
		if (m_ShotCoolDown <= 0)
		{
			// 未使用の弾（非表示状態の弾）を探す
			CShot* pAvaillableShot = UnusedBullet();

			// 未使用の弾が見つかった場合
			if (pAvaillableShot != nullptr)
			{
				// Reloadメソッドにスピードも渡す。弾のスピードは0.5fに設定
				pAvaillableShot->Reload(m_vPosition, 0.5f);

				// 弾を発射したのでクールダウンを設定
				m_ShotCoolDown = ShotCoolTime; // ShotCoolTime は CPlayer.h で定義されていることを確認

				// 効果音を再生
				if (CSoundManager::GetInstance()) 
				{
					CSoundManager::GetInstance()->PlaySE(CSoundManager::SE_Shot);
				}
			}
		}
	}

	// これにより、発射された弾が移動する（CShot::Update()内の移動ロジックが実行される）
	for (int i = 0; i < ShotMax; ++i)
	{
		if (m_pShot[i] != nullptr) // ポインタが有効か確認する癖をつけましょう
		{
			m_pShot[i]->Update();
		}
	}

	// この処理がないと、一度弾を発射したらクールダウンが永遠に終わらず、二度と弾が発射できなくなる。
	if (m_ShotCoolDown > 0)
	{
		m_ShotCoolDown--;
	}

	//プレイヤーのBSphere位置を更新.
	UpdateBSpherePos();

	// 親クラスCCharacterのUpdateメソッドを呼び出し（継承元の更新処理）
	CCharacter::Update();
}

// プレイヤーおよび弾を描画するメソッド（毎フレーム呼び出される想定）
void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera)
{
	// 親クラスCCharacterのDrawメソッドを呼び出し（プレイヤー本体の描画）
	CCharacter::Draw(View, Proj, Light, Camera);

	//全ての弾のDrawメソッドを呼び出し、表示状態の弾のみを描画
	for (int i = 0; i < ShotMax; ++i)
	{
		// ポインタが有効かつ弾が表示状態（CShot::IsDisplay()がtrue）の場合のみ描画
		if (m_pShot[i] != nullptr && m_pShot[i]->IsDisplay())
		{
			m_pShot[i]->Draw(View, Proj, Light, Camera);
		}
	}
}

// プレイヤーと弾を初期状態に戻すメソッド（ゲーム開始時やリトライ時などに呼び出す）
void CPlayer::Init()
{
	for (int i = 0; i < ShotMax; ++i)
	{
		if (m_pShot[i] != nullptr)
		{
			m_pShot[i]->Init();
		}
	}
	m_ShotCoolDown = 0; // クールダウンもリセット
}

// 使用されていない弾（非表示状態の弾）を探して返すヘルパー関数
// これにより、再利用可能な弾オブジェクトを取得できる
CShot* CPlayer::UnusedBullet()
{
	for (int i = 0; i < ShotMax; ++i)
	{
		// ポインタが有効で、かつ弾が非表示状態であれば未使用と判断
		// CShot::IsDisplay() が false を返す弾を探します
		if (m_pShot[i] != nullptr && !m_pShot[i]->IsDisplay())
		{
			return m_pShot[i];
		}
	}
	return nullptr; // 未使用の弾がない場合はnullptrを返す
}

CShot& CPlayer::GetShot(int No)
{
	return *m_pShot[No];
}
