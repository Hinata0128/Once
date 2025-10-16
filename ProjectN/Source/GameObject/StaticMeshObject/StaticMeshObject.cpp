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

	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetRotation(m_vRotation);
	m_pMesh->SetScale(m_vScale);

	//�����_�����O.
	m_pMesh->Render(View, Proj, Light, Camera.vPosition);
}
