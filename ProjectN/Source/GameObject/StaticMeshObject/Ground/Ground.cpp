#include "Ground.h"
#include "StaticMash/StaticMeshManager.h"

Ground::Ground()
{
	AttachMesh(*StaticMeshManager::GetInstance()->GetMeshInstance(StaticMeshManager::CMeshList::Ground));

}

Ground::~Ground()
{
}

void Ground::Update()
{
	//�n�ʃX�N���[���������ɏ���
	//m_vPosition�e�N���X�ɏ����Ă��邩��|�W�V���������ł���.
	//�n�ʂ̔w�i�X�N���[������p�̏���
}
