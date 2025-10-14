#include "CShot.h"
#include "Sound\\CSoundManager.h"      // 効果音再生用
#include "StaticMash/CStaticMeshManager.h" // CStaticMeshManagerのヘッダー

// CShotクラスのコンストラクタ
CShot::CShot()
    : m_Disp    (false)   // 弾の表示状態を初期化
    , m_speed   (0.0f) // 弾の速度を初期化
{
    AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Shot));


    // バウンディングスフィアのインスタンスを生成 (当たり判定用)
    m_pBSphere = new CBoundingSphere();

    Init(); // 弾の初期状態を設定 (位置、スケール、非表示など)
}

// CShotクラスのデストラクタ
CShot::~CShot()
{
    // バウンディングスフィアのインスタンスを破棄
    SAFE_DELETE(m_pBSphere);
}

// 弾の状態を更新するメソッド（毎フレーム呼び出される）
void CShot::Update()
{
    if (m_Disp == true) // 弾が表示状態（アクティブ）の場合のみ更新
    {
        // Z座標を速度分だけ増加させる (奥方向へ進む)
         m_vPosition.z += m_speed + 0.1f; // 0.1f は最低速度または微調整用

        // 弾が画面外に出たかどうかの判定
        // 画面のY軸、X軸方向の端も考慮して、完全に画面外に出たら非表示に戻す
        if (m_vPosition.z >= 30.0 )
        {
            Init(); // 画面外に出たら初期状態に戻し、再利用可能にする
        }

        // バウンディングスフィアの位置を自身の位置に同期させる
        UpdateBoundingSpherePosition();
    }
}

// 弾を描画するメソッド
void CShot::Draw(
    D3DXMATRIX& View, D3DXMATRIX& Proj,
    LIGHT& light, CAMERA& camera)
{
    if (m_Disp == true) // 弾が表示状態の場合のみ描画
    {
        // 親クラスCStaticMeshObjectのDrawメソッドを呼び出し、実際の描画を行う
        CStaticMeshObject::Draw(View, Proj, light, camera);
    }
}

// 弾を発射状態にするメソッド
void CShot::Reload(const D3DXVECTOR3& Pos, float speed)
{
    //弾のサイズをここで調整できる.
    m_vScale = D3DXVECTOR3(1.0f, 1.0f, 5.0f); // 弾のスケールを設定
    m_vPosition = Pos;                     // 発射位置を設定
    m_speed = speed;                       // 弾の速度を設定
    m_Disp = true;                         // 弾を表示状態にする

    // リロード時にバウンディングスフィアの位置を同期し、半径を設定
    if (m_pBSphere) {
        m_pBSphere->SetRadius(0.5f);      // 仮の半径値。弾の大きさに合わせて調整してください
        m_pBSphere->SetPosition(m_vPosition); // 発射位置に合わせる
    }

}

// 弾を初期状態に戻すメソッド（非表示、画面外へ移動など）
void CShot::Init()
{
    m_vPosition = D3DXVECTOR3(0.0f, -1000.0f, 0.0f); // 画面外の初期位置
    m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);     // スケールをリセット
    m_vRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 回転をリセット

    m_Disp = false; // 非表示状態にする
    m_speed = 0.0f; // 速度をリセット

    // 初期化時にバウンディングスフィアの位置をリセットし、当たり判定を無効化
    if (m_pBSphere) {
        m_pBSphere->SetPosition(m_vPosition); // 非表示の位置に合わせる
        m_pBSphere->SetRadius(0.0f);          // 当たり判定を無効化 (半径を0にする)
    }
}

// バウンディングスフィアの位置を自身の位置に同期させる関数
void CShot::UpdateBoundingSpherePosition() {
    if (m_pBSphere) {
        m_pBSphere->SetPosition(m_vPosition);
    }
}