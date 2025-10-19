#include "Player.h"
#include "System/Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "..//..//..//StaticMeshObject/PShot/PShot.h"

Player::Player()
	: m_AnimNo()
	, m_AnimTime()
	, m_AnimSpeed(0.0002)
	, m_BonePos()
	, m_ShotOffset(0.0f, 0.5f, 1.0f)
{
	AttachMesh(*SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player));
	SetScale(0.02f);
	SetPosition(0.f, 0.f, 2.f);

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
	}
	if (GetAsyncKeyState('S') & 0X8000)
	{
		m_vPosition.z -= add_value;
	}
	if (GetAsyncKeyState('D') & 0X8000)
	{
		m_vPosition.x += add_value;
	}
	if (GetAsyncKeyState('A') & 0X8000)
	{
		m_vPosition.x -= add_value;
	}

	//アニメーション切替
	if (GetAsyncKeyState('N') & 0x8000)
	{
		m_AnimNo = 2;		//登場アニメーション
		m_AnimTime = 0.0;	//アニメーション経過時間初期化
		m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
	}
	if (m_AnimNo == 2)
	{
		//アニメーション経過時間を加算
		m_AnimTime += m_AnimSpeed;

		//登場アニメーションの終了時間を超えた？
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 0;		//待機アニメーションへ
			m_AnimTime = 0.0;	//アニメーション経過時間初期化
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}
	if (m_AnimNo == 0)
	{
		//アニメーション経過時間を加算
		m_AnimTime += m_AnimSpeed;

		//登場アニメーションの終了時間を超えた？
		if (m_pMesh->GetAnimPeriod(m_AnimNo) < m_AnimTime)
		{
			m_AnimNo = 1;		//歩きアニメーションへ
			m_AnimTime = 0.0;	//アニメーション経過時間初期化
			m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		}
	}
	//ボーン座標の取得
	m_pMesh->GetPosFromBone("blade_l_head", &m_BonePos);
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for (auto& shot : m_pShotList)
		{
			if (!shot->IsDisplay())
			{
				// 1. 各変換行列を個別に作成する
				D3DXMATRIX matS, matR, matT;
				D3DXMATRIX playerWorldMatrix;

				// スケール行列の作成
				D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);

				// 回転行列の作成 (m_vRotationをオイラー角として使用)
				D3DXMatrixRotationYawPitchRoll(
					&matR,
					m_vRotation.y, m_vRotation.x, m_vRotation.z
				);

				// 移動行列の作成
				D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

				// 2. ワールド行列を構築する (S * R * T の順に乗算)
				// SをRで変換し、その結果をTで変換する
				D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
				D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

				// 3. ローカルのボーン座標をワールド座標に変換する
				D3DXVECTOR3 worldBonePos;
				D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);

				// 4. ワールド座標にオフセットを加えて、最終的な発射位置を決定
				D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

				// 5. 弾を発射
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
