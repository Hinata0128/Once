#include "Player.h"
#include "Sound\\SoundManager.h" // 必要であれば効果音マネージャー

// CPlayerクラスのコンストラクタ
Player::Player()
	// コンストラクタ初期化リストでの m_pShot(0) は配列には不要なので削除しました
{
}

// CPlayerクラスのデストラクタ
Player::~Player()
{
}

// プレイヤーの状態を更新するメソッド（毎フレーム呼び出される想定）
void Player::Update()
{
	float add_value = 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000) 
	{
		m_vPosition.y += add_value;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) 
	{
		m_vPosition.y -= add_value;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
	{
		m_vPosition.x += add_value;	
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_vPosition.x -= add_value;
	}

	//プレイヤーのBSphere位置を更新.
	UpdateBSpherePos();

	// 親クラスCharacterのUpdateメソッドを呼び出し（継承元の更新処理）
	Character::Update();
}

// プレイヤーおよび弾を描画するメソッド（毎フレーム呼び出される想定）
void Player::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera)
{
	// 親クラスCharacterのDrawメソッドを呼び出し（プレイヤー本体の描画）
	Character::Draw(View, Proj, Light, Camera);

}

// プレイヤーと弾を初期状態に戻すメソッド（ゲーム開始時やリトライ時などに呼び出す）
void Player::Init()
{
}

