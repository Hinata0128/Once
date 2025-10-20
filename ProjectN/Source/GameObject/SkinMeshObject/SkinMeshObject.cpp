#include "SkinMeshObject.h"

SkinMeshObject::SkinMeshObject()
	: m_pMesh			( std::make_shared<SkinMesh>() )
	, m_pAnimCtrl		( nullptr )
	, m_AnimNo			( 0 )
	, m_AnimSpeed		( 0.0 )
	, m_AnimTime		( 0.0 )
	, m_BonePos			()
	, m_Loop			( false )
{
}

SkinMeshObject::~SkinMeshObject()
{
	DetachMesh();
}

void SkinMeshObject::Update()
{
	if( m_pMesh == nullptr ){
		return;
	}

	// 時間を進める
	m_AnimTime += m_AnimSpeed;

	// ループ再生が有効な場合
	if (m_Loop)
	{
		double animPeriod = m_pMesh->GetAnimPeriod(m_AnimNo); // ← アニメの全長取得
		if (m_AnimTime > animPeriod)
		{
			m_AnimTime = 0.0; // 最初に戻す
			m_pAnimCtrl->SetTrackPosition(0, 0.0);
		}
	}

	// DirectXアニメーション時間を進める
	m_pAnimCtrl->AdvanceTime(m_AnimSpeed, nullptr);
}

void SkinMeshObject::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	if( m_pMesh == nullptr ){
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pMesh->SetPosition( m_vPosition );
	m_pMesh->SetRotation( m_vRotation );
	m_pMesh->SetScale( m_vScale );

	//レンダリング.
	m_pMesh->Render( View, Proj, Light, Camera.vPosition,
		m_pAnimCtrl );	//クローンを設定
}

//メッシュを接続する.
void SkinMeshObject::AttachMesh(std::shared_ptr<SkinMesh> pMesh)
{
	m_pMesh = pMesh;

	//アニメーションコントローラを取得
	LPD3DXANIMATIONCONTROLLER pAC = m_pMesh->GetAnimationController();

	//アニメーションコントローラのクローンを作成
	if (FAILED(
		pAC->CloneAnimationController(
			pAC->GetMaxNumAnimationOutputs(),
			pAC->GetMaxNumAnimationSets(),
			pAC->GetMaxNumTracks(),
			pAC->GetMaxNumEvents(),
			&m_pAnimCtrl)))
	{
		_ASSERT_EXPR(false, L"アニメーションコントローラのクローン作成失敗");
	}
}
//メッシュを切り離す.
void SkinMeshObject::DetachMesh()
{
	m_pMesh = nullptr;

	SAFE_RELEASE(m_pAnimCtrl);
}

void SkinMeshObject::SetIsLoop(const bool& IsLoop)
{
	m_Loop = IsLoop;
}

