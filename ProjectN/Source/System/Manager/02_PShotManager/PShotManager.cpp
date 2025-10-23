#include "PShotManager.h"

PShotManager* PShotManager::m_pInstance = nullptr;

PShotManager::PShotManager()
{
}

PShotManager::~PShotManager()
{
}

PShotManager* PShotManager::GetInstance()
{
	//インスタンスが作成されていないときに作成する,
}


void PShotManager::Update()
{

}

void PShotManager::Draw()
{

}

void PShotManager::Init()
{
}

void PShotManager::AddPlayerShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton)
{
}

void PShotManager::CleraPlayerShot()
{
}

void PShotManager::ReMovePlayerShot(size_t index)
{
}

const std::vector<std::unique_ptr<PShot>>& PShotManager::GetPlayerShot() const
{
	return m_PlayerShots;
}

PShot* PShotManager::GetPlayrShot(size_t No)
{
	return nullptr;
}

size_t PShotManager::GetPlayerShotCount() const
{
	return size_t();
}