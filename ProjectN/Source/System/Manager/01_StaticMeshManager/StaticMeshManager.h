#pragma once
#include "StaticMash\\StaticMesh.h"

/**********************************************
*	�X�^�e�B�b�N���b�V���}�l�[�W���[�N���X.
**/

class StaticMeshManager
{
public:
	//���f���̎�ނ̗񋓌^.
	enum CMeshList
	{
		Bullet,
		Ground,
		Collision,

		max,
	};
public:
		~StaticMeshManager();

		void Create();
		void Init();

		//�X�^�e�B�b�N�N���X�̃Q�b�g�C���X�^���X������
		StaticMesh* GetMeshInstance(CMeshList MeshNo)
		{
			return m_pMesh[MeshNo];
		};

		//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
		//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
		static StaticMeshManager* GetInstance()
		{
			//�B��̃C���X�^���X���쐬����.
			//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
			static StaticMeshManager s_Instance;	//s_:static�̈Ӗ�.
			return &s_Instance;
		}


private:
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	StaticMeshManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	StaticMeshManager(const StaticMeshManager& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	StaticMeshManager& operator = (const StaticMeshManager& rhs) = delete;



	StaticMesh* m_pMesh[CMeshList::max];

};