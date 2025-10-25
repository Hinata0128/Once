#include "Player.h"
#include "System/00_Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "..//..//..//StaticMeshObject/ShotBase/PShot/PShot.h"

#include "System/00_Manager/02_PShotManager/PShotManager.h"

#include "System/02_Singleton/Timer.h"

constexpr float zero = 0.0f;

Player::Player()
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

    m_pShotManager = PShotManager::GetInstance();
}

Player::~Player()
{
}

void Player::Update()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);

    //ローカル変数宣言場所.
    constexpr float add_value = 0.1f;

    //クールタイムの実装.
    float deltaTime = Timer::GetInstance().DeltaTime();

    bool isMoving = false;  // 移動しているかフラグ
    int newAnimNo = -1;     // 今回再生すべきアニメーション

    //クールタイム(0.5f)が0.0fになったら弾を発射.
    if (m_CoolTime >= zero)
    {
        m_ShotCoolDown -= deltaTime;
    }

    D3DXVECTOR3  ForwardAndBackward = Player_WS();
    D3DXVECTOR3  LeftAndRight       = Player_AD();

    // キー入力による移動
    if (GetAsyncKeyState('W') & 0x8000)
    {
        m_vPosition += ForwardAndBackward * add_value;
        isMoving = true; 
        newAnimNo = 2;  // 走るアニメーション
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        m_vPosition -= ForwardAndBackward * add_value;
        isMoving = true;
        newAnimNo = 0;  // 後退アニメーション
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        m_vPosition += LeftAndRight * add_value;
        isMoving = true;
        newAnimNo = 2;  // 走るアニメーション
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        m_vPosition -= LeftAndRight * add_value;
        isMoving = true;
        newAnimNo = 2;  // 走るアニメーション
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        m_vRotation.y += add_value;
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
        if (m_AnimNo != 0)  // 待機アニメーションは0と仮定
        {
            m_AnimNo = 0;
            m_AnimTime = 0.0f;
            m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
        }
    }

    //ボーン座標の取得
    m_pMesh->GetPosFromBone("blade_l_head", &m_BonePos);

    //弾を撃つボタン.
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_ShotCoolDown <= zero)
    {
        //アニメーションを2番にする.
        m_AnimNo = 2;
        //アニメーションの時間を初期化.
        m_AnimTime = 0.0f;
        //アニメーションを変更.
        m_pMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

        //各変換行列を作成.
        D3DXMATRIX matS, matR, matT, playerWorldMatrix;
        D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
        D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
        D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
        D3DXMatrixMultiply(&playerWorldMatrix, &matS, &matR);
        D3DXMatrixMultiply(&playerWorldMatrix, &playerWorldMatrix, &matT);

        D3DXVECTOR3 worldBonePos;
        D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &playerWorldMatrix);

        D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

        D3DXVECTOR3 Dir = Player_WS();
        D3DXVec3Normalize(&Dir, &Dir);
        // Manager に弾を追加
        m_pShotManager->AddPlayerShot(shotPos, Dir);

        // クールタイムリセット
        m_ShotCoolDown = m_CoolTime;
    }

    // アニメーション更新
    m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);

    // 弾の更新
    m_pShotManager->Update();

    Character::Update();
}


void Player::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	Character::Draw();

    m_pShotManager->Draw();
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
//W・Sの前進後退用関数.
D3DXVECTOR3 Player::Player_WS() const
{
    // Player の回転から前方方向ベクトルを計算
    D3DXVECTOR3 dir;
    
    dir.x = sinf(m_vRotation.y);
    dir.y = zero;
    dir.z = cosf(m_vRotation.y);
    return dir;

}
//A・Dの左右用関数.
D3DXVECTOR3 Player::Player_AD() const
{
    D3DXVECTOR3 dir;
    dir.x = cosf(m_vRotation.y);
    dir.y = zero;
    dir.z = -sinf(m_vRotation.y);
    return dir;
}

