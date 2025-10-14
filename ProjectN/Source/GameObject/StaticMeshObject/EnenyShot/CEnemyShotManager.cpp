#include "CEnemyShotManager.h"

CEnemyShotManager* CEnemyShotManager::m_pInstance = nullptr;

CEnemyShotManager::CEnemyShotManager()
{
}

CEnemyShotManager::~CEnemyShotManager()
{
    ClearAllHomingShot();
}

CEnemyShotManager* CEnemyShotManager::GetInstance()
{
    //インスタンスがまだ生成されていなければ新しく生成する.
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CEnemyShotManager();
    }
    return m_pInstance;
}

//全てのホーミング弾を更新する.
void CEnemyShotManager::Update()
{
    //イテレータを使ってループすることで、途中で要素を削除する.
    for (auto it = m_homingShots.begin(); it != m_homingShots.end();)
    {
        (*it)->Update();    //各ホーミング弾のUpdate関数を呼び出す.

        //ホーミング弾が非アクティブ(寿命切れや衝突など)になったら削除する.
        if (!(*it)->IsActive())
        {
            delete* it; //ヒープメモリから弾のオブジェクトを解放.
            it = m_homingShots.erase(it);   //vectorからポインタを削除し、次のイテレータを取得
        }
        else
        {
            ++it;   //次のホーミング弾へ進む.
        }
    }
}

void CEnemyShotManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //m_homingShotsの配列の最初から最後までを回す。長いfor文で書くとオーバーフローをしないようにする利点もある。
    for (EnemyShot* shot : m_homingShots)
    {
        if (shot->IsActive())
        {
            shot->Draw(View, Proj, Light, Camera);
        }
    }
}

//新しいホーミング弾を作成し、管理リストに追加する.
void CEnemyShotManager::AddHomingShot(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer)
{
    EnemyShot* newShot = new EnemyShot();

    //生成した弾を初期化.
    newShot->Init(position, initalDirection, pTargetPlayer);

    //管理リストに追加.
    m_homingShots.push_back(newShot);
}

//全てのホーミング弾をリストから削除し、メモリを解放する.
void CEnemyShotManager::ClearAllHomingShot()
{
    for (EnemyShot* shot : m_homingShots)
    {
        SAFE_DELETE (shot);    //各弾のメモリを解放.
    }
    m_homingShots.clear();  //vectorの中身をクリア.
}

void CEnemyShotManager::RemoveShot(size_t index)
{
    if (index < m_homingShots.size())
    {
        SAFE_DELETE(m_homingShots[index]);   //オブジェクトの解放.
        m_homingShots.erase(m_homingShots.begin() + index);   //コンテナから要素を削除.
    }

}

void CEnemyShotManager::Init()
{
    ClearAllHomingShot();
}
