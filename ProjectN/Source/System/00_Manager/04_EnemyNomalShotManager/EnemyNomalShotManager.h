#pragma once
#include <vector>

#include "..//..//..//GameObject/StaticMeshObject/ShotBase/EnemyNomalShot/EnemyNomalShot.h"

/*****************************************************************
*	�G�̒ʏ�U���}�l�[�W���[�N���X.
**/

class EnemyNomalShotManager
{
public:
	~EnemyNomalShotManager();

	static EnemyNomalShotManager* GetInstance();

	void Update();
	void Draw();

	//�G�̒ʏ�e���쐬���āA�Ǘ����X�g�ɒǉ�������.
	void AddEnemyNomalShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton);

	void ReMoveEnemyNomalShot(size_t index);

	const std::vector<std::unique_ptr<EnemyNomalShot>>& GetEnemyNomalShot() const;

	EnemyNomalShot* GetEnemyNomalShot(size_t No);

	//�G�̒ʏ�e���擾.
	size_t GetEnemyNomalShotCount() const;
private:
	EnemyNomalShotManager();

	EnemyNomalShotManager(const EnemyNomalShotManager& rhs) = delete;
	EnemyNomalShotManager& operator = (const EnemyNomalShotManager& rhs) = delete;
private:
	static EnemyNomalShotManager* m_pInstance;	//�V���O���g���C���X�^���X.

	std::vector<std::unique_ptr<EnemyNomalShot>> m_EnemyNomalShot;
};