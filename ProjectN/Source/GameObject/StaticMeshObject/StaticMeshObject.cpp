#include "StaticMeshObject.h"

StaticMeshObject::StaticMeshObject()
	: m_pMesh			( nullptr )
{
}

StaticMeshObject::~StaticMeshObject()
{
	DetachMesh();
}

void StaticMeshObject::Update()
{
	if( m_pMesh == nullptr ){
		return;
	}
}

void StaticMeshObject::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	if (m_pMesh == nullptr) {
		return;
	}

	//描画直前で座標や回転情報などを更新.
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetRotation(m_vRotation);
	m_pMesh->SetScale(m_vScale);

	//レンダリング.
	m_pMesh->Render(View, Proj, Light, Camera.vPosition);
}
