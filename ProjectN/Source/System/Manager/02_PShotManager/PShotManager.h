#pragma once
#include <vector>	//�e�𐶐��Ɣj�������Ă���.

#include "..//..//..//GameObject/StaticMeshObject/PShot/PShot.h"


class PShotManager
{
public:
	~PShotManager();

	static PShotManager* GetInstance();

	void Update();
	void Draw();

	//�v���C���[�̒ʏ�e���쐬���āA�Ǘ����X�g�ɒǉ�������.
	void AddPlayerShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton);

	void ReMovePlayerShot(size_t index);

	const std::vector<std::unique_ptr<PShot>>& GetPlayerShot() const;

	PShot* GetPlayrShot(size_t No);

	//�v���C���[�̒e���擾.
	size_t GetPlayerShotCount() const;
private:
	PShotManager();

	PShotManager(const PShotManager& rhs) = delete;
	PShotManager& operator = (const PShotManager& rhs) = delete;

private:
	static PShotManager* m_pInstance;	//�V���O���g���C���X�^���X.

	std::vector<std::unique_ptr<PShot>> m_PlayerShot;
};