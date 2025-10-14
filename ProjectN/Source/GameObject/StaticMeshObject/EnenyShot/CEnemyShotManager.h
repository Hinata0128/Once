#pragma once
#include <vector>
#include "GameObject/StaticMeshObject/EnenyShot/EnemyShot.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"

/*****************************************************************
*	�z�[�~���O�e�}�l�[�W���[.
**/

class CEnemyShotManager
{
public:

	~CEnemyShotManager();
	//�V���O���g���C���X�^���X���擾����ÓI���\�b�h.
	static CEnemyShotManager* GetInstance();

	void Update();

	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera);

	//�V�����z�[�~���O�e���쐬���A�Ǘ����X�g�ɒǉ�����.
	void AddHomingShot(const D3DXVECTOR3& position, const D3DXVECTOR3& initalDirection, CPlayer* pTargetPlayer);

	//�S�Ẵz�[�~���O�e�����X�g����폜���A���������������.
	void ClearAllHomingShot();

	void RemoveShot(size_t index);

	void Init();


	const std::vector<EnemyShot*>& GetHomingShots() const { return m_homingShots; }

	EnemyShot* GetShot(size_t No)
	{
		if (No < m_homingShots.size())
		{
			return m_homingShots[No];
		}
		return nullptr;
	}

	//�z�[�~���O�e�̐����擾����֐�
	size_t GetShotCount() const { return m_homingShots.size(); }

private:
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CEnemyShotManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CEnemyShotManager(const CEnemyShotManager& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CEnemyShotManager& operator = (const CEnemyShotManager& rhs) = delete;
private:
	static CEnemyShotManager* m_pInstance;	//�V���O���g���C���X�^���X.

	//���݃A�N�e�B�u�ȃz�[�~���O�e��ێ�����R���e�i.
	std::vector<EnemyShot*> m_homingShots;

};
