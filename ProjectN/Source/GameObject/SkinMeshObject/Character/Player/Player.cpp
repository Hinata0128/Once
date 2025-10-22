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
	SetScale(0.04f);
	SetPosition(0.f, 0.f, 2.f);

	//アニメーションの速度を
	m_AnimSpeed = 0.02f;
	//m_AnimSpeed = 0.0002f;

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

    bool isMoving = false;  // 移動しているかフラグ
    int newAnimNo = -1;     // 今回再生すべきアニメーション

    // キー入力による移動
    if (GetAsyncKeyState('W') & 0x8000)
    {
        m_vPosition.z += add_value;
        isMoving = true;
        newAnimNo = 2;  // 走るアニメーション
    }
    else if (GetAsyncKeyState('S') & 0x8000)
    {
        m_vPosition.z -= add_value;
        isMoving = true;
        newAnimNo = 0;  // 後退アニメーション
    }
    else if (GetAsyncKeyState('D') & 0x8000)
    {
        m_vPosition.x += add_value;
        isMoving = true;
        newAnimNo = 2;  // 走るアニメーション
    }
    else if (GetAsyncKeyState('A') & 0x8000)
    {
        m_vPosition.x -= add_value;
        isMoving = true;
        newAnimNo = 2;  // 走るアニメーション
    }

    // 移動している場合のみアニメーションを切り替え
    if (isMoving)
    {
        if (m_AnimNo != newAnimNo)
        {
            m_AnimNo = newAnimNo;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
    }
    else
    {
        // 移動していなければ待機アニメーション
        if (m_AnimNo != 0)  // 待機アニメーションは0と仮定
        {
            m_AnimNo = 0;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
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

    // 弾の更新
    for (auto& shot : m_pShotList)
    {
        shot->Update();
    }

    // アニメーション更新
    m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);
}


void Player::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	Character::Draw();

	for (auto& shot : m_pShotList)
	{
		shot->Draw();
	}
}

void Player::Stop()
{
    if (m_pAnimCtrl)
    {
        // アニメーション進行を止める
        m_pAnimCtrl->AdvanceTime(0.0f, nullptr);

        D3DXTRACK_DESC trackDesc;
        m_pAnimCtrl->GetTrackDesc(0, &trackDesc);
        trackDesc.Enable = FALSE;
        m_pAnimCtrl->SetTrackDesc(0, &trackDesc);
    }
}

