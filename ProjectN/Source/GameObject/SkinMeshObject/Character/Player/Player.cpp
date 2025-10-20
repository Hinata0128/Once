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
	//SetScale(0.002f);
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

    // ボーン座標の取得
    m_pMesh->GetPosFromBone("head", &m_BonePos);

    // 弾の発射
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        // 射撃用アニメーション
        if (m_AnimNo != 2)  // 仮に射撃アニメーションを2とする
        {
            m_AnimNo = 2;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }

        for (auto& shot : m_pShotList)
        {
            if (!shot->IsDisplay())
            {
                D3DXMATRIX matS, matR, matT, playerWorldMatrix;
                D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
                D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
                D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
                D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
                D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

                D3DXVECTOR3 worldBonePos;
                D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);
                D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

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

