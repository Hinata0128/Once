#include "EnemyNomal.h"
#include "System/00_Manager/00_SkinMeshManager/SkinMeshManager.h"
#include "System/00_Manager/04_EnemyNomalShotManager/EnemyNomalShotManager.h"
#include "System/02_Singleton/Timer.h"

constexpr float zero = 0.0f;

EnemyNomal::EnemyNomal()
    : m_pENShotManager(nullptr)
{
    SkinMesh* raw_mesh = SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Enemy);
    auto shared_mesh = std::shared_ptr<SkinMesh>(raw_mesh, [](SkinMesh*) {});
    AttachMesh(shared_mesh);

    SetScale(0.002f);
    SetPosition(0.0f, 0.0f, 10.0f);

    m_AnimSpeed = 0.0002f;

    m_pENShotManager = EnemyNomalShotManager::GetInstance();

    // クールタイム初期化
    m_ShotCoolDown = 0.0f;
    m_CoolTime = 1.0f; // 1秒ごとに発射
}

EnemyNomal::~EnemyNomal() {}

void EnemyNomal::Update()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);
    float deltaTime = Timer::GetInstance().DeltaTime();

    // クールタイム減算
    m_ShotCoolDown -= deltaTime;
    if (m_ShotCoolDown < 0.0f) m_ShotCoolDown = 0.0f;

    // ボーン座標取得
    m_pMesh->GetPosFromBone("entotu_Joint", &m_BonePos);

    // アニメーション更新
    m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);

    // 弾の発射（自動）
    if (m_ShotCoolDown == 0.0f)
    {
        // 変換行列作成
        D3DXMATRIX matS, matR, matT, enemyWorldMatrix;
        D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, m_vScale.z);
        D3DXMatrixRotationYawPitchRoll(&matR, m_vRotation.y, m_vRotation.x, m_vRotation.z);
        D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
        D3DXMatrixMultiply(&enemyWorldMatrix, &matS, &matR);
        D3DXMatrixMultiply(&enemyWorldMatrix, &enemyWorldMatrix, &matT);

        // ボーン座標をワールド座標に変換
        D3DXVECTOR3 worldBonePos;
        D3DXVec3TransformCoord(&worldBonePos, &m_BonePos, &enemyWorldMatrix);

        D3DXVECTOR3 shotPos = worldBonePos + m_ShotOffset;

        // 弾は常に -Z 方向
        D3DXVECTOR3 Dir = Enemy_WS();
        D3DXVec3Normalize(&Dir, &Dir);

        // 弾を追加
        m_pENShotManager->AddEnemyNomalShot(shotPos, Dir);

        // クールタイムリセット
        m_ShotCoolDown = m_CoolTime;
    }

    // 弾の更新
    m_pENShotManager->Update();

    EnemyBase::Update();
}

void EnemyNomal::Draw()
{
    m_pMesh->SetAnimSpeed(m_AnimSpeed);
    EnemyBase::Draw();
    m_pENShotManager->Draw();
}

// 弾の飛ぶ方向（常に -Z）
D3DXVECTOR3 EnemyNomal::Enemy_WS() const
{
    return D3DXVECTOR3(0.0f, 0.0f, -1.0f);
}
