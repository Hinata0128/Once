#include "Player.h"
#include "System/Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "..//..//..//StaticMeshObject/PShot/PShot.h"

Player::Player()
	: m_ShotOffset(0.0f, 0.5f, 1.0f)
{
	//AttachMesh(*SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player));
	SkinMesh* raw_mesh = SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player);

	auto shared_mesh = std::shared_ptr<SkinMesh>(raw_mesh,[](SkinMesh*){});

	//AttachMesh に shared_ptr を渡す
	AttachMesh(shared_mesh);
	SetScale(0.06f);
	SetPosition(0.f, 0.f, 2.f);

	//アニメーションの速度を
	m_AnimSpeed = 0.02f;

	//今はプレイヤークラスで弾の出る出ないの確認をしたかったのでここに書いている.
	const int SHOT_COUNT = 10;
	m_pShotList.reserve(SHOT_COUNT); // メモリ事前確保

	for (int i = 0; i < SHOT_COUNT; ++i)
	{
		auto shot = std::make_unique<PShot>();
		shot->Init();          // 初期化
		shot->SetDisplay(false); // 非表示にしておく
		m_pShotList.push_back(std::move(shot));
	}
}

Player::~Player()
{
}

void Player::Update()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);

	constexpr float add_value = 0.1f;

	if (GetAsyncKeyState('W') & 0X8000)
	{
		m_vPosition.z += add_value;
		m_AnimNo = 2;		
		m_AnimTime = 0.0;	//アニメーション経過時間初期化
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);		
	}
	if (GetAsyncKeyState('S') & 0X8000)
	{
		m_vPosition.z -= add_value;
		m_AnimNo = 0;		
		m_AnimTime = 0.0;	//アニメーション経過時間初期化
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}
	if (GetAsyncKeyState('D') & 0X8000)
	{
		m_vPosition.x += add_value;
		m_AnimNo = 0;		
		m_AnimTime = 0.0;	//アニメーション経過時間初期化
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}
	if (GetAsyncKeyState('A') & 0X8000)
	{
		m_vPosition.x -= add_value;
		m_AnimNo = 0;		
		m_AnimTime = 0.0;	//アニメーション経過時間初期化
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}

	//ボーン座標の取得
	m_pMesh->GetPosFromBone("blade_l_head", &m_BonePos);
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_AnimNo = 2;
		m_AnimTime = 0.0f;
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		for (auto& shot : m_pShotList)
		{
			if (!shot->IsDisplay())
			{
				//各変換行列を個別に作成する.
				D3DXMATRIX matS, matR, matT;
				D3DXMATRIX playerWorldMatrix;

				//スケール行列の作成.
				D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

				//回転行列の作成 (m_vRotationをオイラー角として使用).
				D3DXMatrixRotationYawPitchRoll(
					&matR,
					m_vRotation.y, m_vRotation.x, m_vRotation.z
				);

				//移動行列の作成.
				D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

				//ワールド行列を構築する (S * R * T の順に乗算).
				//SをRで変換し、その結果をTで変換する.
				D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
				D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

				//ローカルのボーン座標をワールド座標に変換する.
				D3DXVECTOR3 worldBonePos;
				D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);

				//ワールド座標にオフセットを加えて、最終的な発射位置を決定.
				D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

				//弾を発射.
				shot->Reload(shotPos, 0.2f);
				shot->SetDisplay(true);
				break;
			}
		}
	}

	for (auto& shot : m_pShotList)
	{
		shot->Update();
	}
}

//アニメーションの管理を修正するよう.
//void Player::Update()
//{
//	m_pMesh->SetAnimSpeed(m_AnimSpeed);
//
//	constexpr float add_value = 0.1f;
//
//	// 現在のアニメーション番号を保持
//	int new_AnimNo = m_AnimNo;
//
//	bool Is_Moving = false;
//
//	if (GetAsyncKeyState('W') & 0X8000)
//	{
//		m_vPosition.z += add_value;
//		new_AnimNo = 2; // 歩きアニメーション
//		m_pMesh->ChangeAnimSet_StartPos(m_AnimNo, m_AnimSpeed, m_pAnimCtrl);
//		Is_Moving = true;
//	}
//	else if (GetAsyncKeyState('S') & 0X8000)
//	{
//		m_vPosition.z -= add_value;
//		new_AnimNo = 3; // 別の歩きアニメーション
//		Is_Moving = true;
//	}
//	else if (GetAsyncKeyState('D') & 0X8000)
//	{
//		m_vPosition.x += add_value;
//		new_AnimNo = 2; // 歩きアニメーション
//		Is_Moving = true;
//	}
//	else if (GetAsyncKeyState('A') & 0X8000)
//	{
//		m_vPosition.x -= add_value;
//		new_AnimNo = 2; // 歩きアニメーション
//		Is_Moving = true;
//	}
//	// ここで移動キー入力がない場合、待機アニメーション (例: 0) に設定
//	else if (m_AnimNo != 0)
//	{
//		// 移動を停止したら待機アニメーションへ移行
//		new_AnimNo = 0;
//	}
//
//	// アニメーションの切り替え処理
//	if (new_AnimNo != m_AnimNo)
//	{
//		m_AnimNo = new_AnimNo;
//		m_AnimTime = 0.0;	// アニメーション切り替え時のみ時間をリセット
//		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
//	}
//
//	// ★常にアニメーション時間を更新する
//	// (特定のキーを押している/アニメーションが再生中であれば)
//	if (m_pMesh) // メッシュが存在する場合にのみ実行
//	{
//		// 1. アニメーション経過時間を加算
//		m_AnimTime += m_AnimSpeed;
//
//		// 2. 現在のアニメーションの終了時間（周期）を取得
//		double anim_period = m_pMesh->GetAnimPeriod(m_AnimNo);
//
//		// 3. 終了時間を超えたか判定し、ループ処理を実行
//		if (anim_period > 0.0 && m_AnimTime >= anim_period)
//		{
//			// ★ループ処理：終了時間を超えた分だけ時間を減算する
//			//   (例: 周期が1.0で、時間が1.02になったら、時間を0.02に戻す)
//			m_AnimTime -= anim_period;
//
//			// NOTE: ここで m_AnimNo の切り替え（例: 待機に戻す）は行いません。
//			// 待機/移動の切り替えは、キー入力のロジックによって制御されます。
//		}
//	}
//	//アニメーション切替
//	if (GetAsyncKeyState('N') & 0x8000)
//	{
//		m_AnimNo = 2;		//登場アニメーション
//		m_AnimTime = 0.0;	//アニメーション経過時間初期化
//		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
//	}
//	if (m_AnimNo == 2)
//	{
//		//アニメーション経過時間を加算
//		m_AnimTime += m_AnimSpeed;
//
//		//登場アニメーションの終了時間を超えた？
//		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
//		{
//			m_AnimNo = 0;		//待機アニメーションへ
//			m_AnimTime = 0.0;	//アニメーション経過時間初期化
//			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
//		}
//	}
//	if (m_AnimNo == 0)
//	{
//		//アニメーション経過時間を加算
//		m_AnimTime += m_AnimSpeed;
//
//		//登場アニメーションの終了時間を超えた？
//		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
//		{
//			m_AnimNo = 1;		//歩きアニメーションへ
//			m_AnimTime = 0.0;	//アニメーション経過時間初期化
//			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
//		}
//	}
//	//ボーン座標の取得
//	m_pMesh->GetPosFromBone("blade_l_head", &m_BonePos);
//
//	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
//	{
//		m_AnimNo = 2;
//		m_AnimTime = 0.0f;
//		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
//		for (auto& shot : m_pShotList)
//		{
//			if (!shot->IsDisplay())
//			{
//				// 1. 各変換行列を個別に作成する
//				D3DXMATRIX matS, matR, matT;
//				D3DXMATRIX playerWorldMatrix;
//
//				// スケール行列の作成
//				D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
//
//				// 回転行列の作成 (m_vRotationをオイラー角として使用)
//				D3DXMatrixRotationYawPitchRoll(
//					&matR,
//					m_vRotation.y, m_vRotation.x, m_vRotation.z
//				);
//
//				// 移動行列の作成
//				D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
//
//				// 2. ワールド行列を構築する (S * R * T の順に乗算)
//				// SをRで変換し、その結果をTで変換する
//				D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
//				D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);
//
//				// 3. ローカルのボーン座標をワールド座標に変換する
//				D3DXVECTOR3 worldBonePos;
//				D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);
//
//				// 4. ワールド座標にオフセットを加えて、最終的な発射位置を決定
//				D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;
//
//				// 5. 弾を発射
//				shot->Reload(shotPos, 0.2f);
//				shot->SetDisplay(true);
//				break;
//			}
//		}
//	}
//
//	for (auto& shot : m_pShotList)
//	{
//		shot->Update();
//	}
//}


void Player::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	Character::Draw(View, Proj, Light, Camera);

	for (auto& shot : m_pShotList)
	{
		shot->Draw(View, Proj, Light, Camera);
	}
}
