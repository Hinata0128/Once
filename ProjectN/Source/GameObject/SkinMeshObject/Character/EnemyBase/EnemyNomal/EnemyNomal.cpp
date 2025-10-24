#include "EnemyNomal.h"
#include "System//00_Manager//00_SkinMeshManager//SkinMeshManager.h"	//SkinMesh表示用.

EnemyNomal::EnemyNomal()
{
	//AttachMesh(*SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Player));
	SkinMesh* raw_mesh = SkinMeshManager::GetInstance()->GetSkinMeshInstance(SkinMeshManager::SkinList::Enemy);
	auto shared_mesh = std::shared_ptr<SkinMesh>(raw_mesh, [](SkinMesh*) {});
	AttachMesh(shared_mesh);

	SetScale(0.002f);
	SetPosition(0.0f, 0.0f, 10.0f);

	//アニメーションの速度を
	m_AnimSpeed = 0.0002f;
}

EnemyNomal::~EnemyNomal()
{
}

void EnemyNomal::Update()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);
	
	//ボーン座標の取得
	m_pMesh->GetPosFromBone("entotu_Joint", &m_BonePos);

	m_AnimNo = 1;
	//アニメーションの時間を初期化.
	m_AnimTime = 0.0f;

	// アニメーション更新
	m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);

	EnemyBase::Update();
}

void EnemyNomal::Draw()
{
	m_pMesh->SetAnimSpeed(m_AnimSpeed);

	EnemyBase::Draw();
}
