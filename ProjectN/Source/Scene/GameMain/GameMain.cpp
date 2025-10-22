#include "GameMain.h"
#include "Sound/SoundManager.h"
#include "Effect//Effect.h"

GameMain::GameMain()
	: CSceneBase			() 
	, m_pStcMeshObj			( std::make_unique<StaticMeshObject>() )

	, m_pGround				( std::make_unique<Ground>() )

	, m_pPlayer				(std::make_unique<Player>())

{
	m_pDx11 = DirectX11::GetInstance();
	m_pDx9	= DirectX9::GetInstance();

	//カメラの位置を変更できるところ.
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f); 
	//カメラを見ているところを変更できるところ.
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//ライト情報
	m_Light.vDirection = D3DXVECTOR3(1.5f, 1.f, -1.f);		//ライト方向.
	Initialize();
}

GameMain::~GameMain()
{
	// 外部で作成しているので、ここでは破棄しない
	m_hWnd = nullptr;
	m_pDx11 = nullptr;
	m_pDx9 = nullptr;
}

void GameMain::Initialize()
{

	// カメラの位置を初期化
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);
}

void GameMain::Create()
{

}

void GameMain::Update()
{

	//Effect制御
	{
		//エフェクトのインスタンスごとに必要なハンドル
		//※３つ表示して制御するなら３つ必要になる
		static ::EsHandle hEffect = -1;

		if (GetAsyncKeyState('Y') & 0x0001) {
			hEffect = Effect::Play(Effect::Test0, D3DXVECTOR3(0.f, 1.f, 0.f));

			//拡大縮小
			Effect::SetScale(hEffect, D3DXVECTOR3(0.8f, 0.8f, 0.8f));

			//回転(Y軸回転)
			Effect::SetRotation(hEffect, D3DXVECTOR3(0.f, D3DXToRadian(90.0f), 0.f));

			//位置を再設定
			Effect::SetLocation(hEffect, D3DXVECTOR3(0.f, 1.f, 1.f));
		}
		if (GetAsyncKeyState('T') & 0x0001) {
			Effect::Stop(hEffect);
		}
	}
	//地面.
	m_pGround->Update();

	m_pPlayer->Update();

}

void GameMain::Draw()
{
	Camera();
	Projection();

	PreDraw();


		//地面表示.
	m_pGround->Draw();
	m_pPlayer->Draw();
	
	//Effectクラス
	Effect::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_Camera);
}

HRESULT GameMain::LoadData()
{
	return S_OK;
}

void GameMain::Camera()
{
	D3DXVECTOR3 cam_pos = m_Camera.vPosition;
	D3DXVECTOR3 cam_look = m_Camera.vLook;
	D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//上方（ベクトル）.

	//ビュー（カメラ）変換.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)ビュー計算結果.
		&cam_pos, &cam_look, &vUpVec);
}

//プロジェクション関数.
void GameMain::Projection()
{
	//y方向の視野角。数値を大きくしたら視野が狭くなる.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//ラジアン値.
	//アスペクト（幅÷高さ）.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;
	float far_z = 100.0f;

	//プロジェクション（射影）変換.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,	//(out)プロジェクション計算結果.
		fov_y,		//視野角（FOV：Field of View）.
		aspect,		//アスペクト.
		near_z,		//近いビュー平面のz値.
		far_z);	//遠いビュー平面のz値.
}

