#pragma once

#include "SkinMesh//SkinMesh.h"

/*****************************************************************************
*	�X�L�����b�V���}�l�[�W���[�N���X
*	�ŏI�I�ɂ́A�A�Z�b�g�N���X���쐬���Ă����ɃX�^�e�B�b�N�ƃX�L�����b�V���𓝍�������.
*	���̓V���O���g���ɂ��Ă����܂�.
**/

class SkinMeshManager
{
public:
	//�X�L�����f���̎�ނ̗񋓌^.
	enum class SkinList
	{
		//�����ɖ��O�������Ă���.
		Player,

		max,
	};
public:
	~SkinMeshManager();

	void Create();
	void Init();

	//�X�L�����b�V���N���X��GetInstance������
	SkinMesh* GetSkinMeshInstance(SkinList SkinNo);

	static SkinMeshManager* GetInstance();
private:
	SkinMeshManager();
	SkinMeshManager(const SkinMeshManager& rhs) = delete;
	//�R�s�[�̋֎~.
	SkinMeshManager& operator = (const SkinMeshManager& rhs) = delete;

	std::unique_ptr<SkinMesh> m_pSkin[static_cast<int>(SkinList::max)];

protected:

};
