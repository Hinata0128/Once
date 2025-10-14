#include "EnemyShot.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"

EnemyShot::EnemyShot()
    : m_vposition       (0, 0, 0)
    , m_velocity        (0, 0, 0)
    , m_speed           (0.f)
    , m_homingStrength  (0.f)
    , m_lifeTime        (0.f)
    , m_elapsedTime     (0.f)
    , m_pTargetPlayer   (nullptr)
    , m_bIsActive       (false)
{
    AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Shot));
}

EnemyShot::~EnemyShot()
{
}

void EnemyShot::Init(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer)
{
    m_vposition = position; //初期位置を設定.
    SetPosition(position.x, position.y, position.z);

    //初期方向を正規化.
    D3DXVec3Normalize(&m_velocity, &initalDirection);
    //弾の移動速度を設定.
    m_speed = 3.f;
    //方向をベクトルに速度をかけて速度ベクトルにする.
    m_velocity *= m_speed;

    //ホーミングの強さ(0.0: 直進, 1.0: 瞬時にターゲットのほうへ).
    //小さいほど緩やかなカーブになる.
    m_homingStrength = 0.1f;
    m_lifeTime = 5.f;      //弾の寿命を10秒で設定.
    m_elapsedTime = 0.f;    //経過時間をリセット.

    m_pTargetPlayer = pTargetPlayer;    //追尾対象をプレイヤーに設定.

    //弾をアクティブ状態にする.
    m_bIsActive = true;
}

void EnemyShot::Update()
{
    if (!m_bIsActive)
    {
        return;
    }

    //弾の寿命の管理.
    float deltaTime = 1.f / 100.f;

    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_lifeTime)
    {
        m_bIsActive = false;    //寿命が尽きたら非アクティブにする.
        return;                 //これ以上更新しない.
    }

    //ホーミングロジック.
    //プレイヤーが生存している時のみ追尾.
    if (m_pTargetPlayer)
    {
        D3DXVECTOR3 playerPos = m_pTargetPlayer->GetPosition();     //プレイヤーの現在座標を取得.
        D3DXVECTOR3 toPlayer = playerPos - m_vposition;             //プレイヤーへの進行方向をベクトルを計算.

        D3DXVec3Normalize(&toPlayer, &toPlayer);    //プレイヤーへの方向ベクトルを正規化.

        // 現在の速度ベクトルとプレイヤーへの方向ベクトルを線形補間して、ホーミングを実現.
        D3DXVECTOR3 newVelocityDirection;
        D3DXVECTOR3 currentDirection;
        D3DXVec3Normalize(&currentDirection, &m_velocity);

        D3DXVec3Lerp(&newVelocityDirection, &currentDirection, &toPlayer, m_homingStrength);
        //再度正規化して方向ベクトルにする.
        D3DXVec3Normalize(&newVelocityDirection, &newVelocityDirection);
        //新しい方向と速さで速度を更新.
        m_velocity = newVelocityDirection * m_speed;
    }
    //位置の更新.
    m_vposition += m_velocity * deltaTime;
    //CStaticMeshObjectの位置も更新.
    SetPosition(m_vposition.x, m_vposition.y, m_vposition.z);
    //当たり判定を更新.
    UpdateBSpherePos();
}

void EnemyShot::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //非アクティブなら表示しない.
    if (!m_bIsActive)
    {
        return;
    }
    //弾のサイズを変更できる.
    m_vScale = D3DXVECTOR3(5.0f, 5.0f, 1.0f); // 弾のスケールを設定
    CStaticMeshObject::Draw(View, Proj, Light, Camera);
}
