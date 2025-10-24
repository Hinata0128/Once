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
	static PShotManager s_Instance;
	return &s_Instance;
}


void PShotManager::Update()
{
	for (auto it = m_PlayerShot.begin(); it != m_PlayerShot.end();)
	{
		(*it)->Update();

		//¶‘¶‚µ‚Ä‚¢‚È‚¢’e‚Ííœ.
		if (!(*it)->IsActive())
		{
			it = m_PlayerShot.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void PShotManager::Draw()
{
	for (std::unique_ptr<PShot>& PShot: m_PlayerShot)
	{
		PShot->Draw();
	}
}

void PShotManager::AddPlayerShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton)
{
	constexpr float Speed = 0.05f;

	auto PlayerShot = std::make_unique<PShot>();

	PlayerShot->Reload(Pos, InitDirecton , Speed);

	PlayerShot->SetDisplay(true);

	m_PlayerShot.push_back(std::move(PlayerShot));
}

void PShotManager::ReMovePlayerShot(size_t index)
{
	if (index < m_PlayerShot.size())
	{
		m_PlayerShot.erase(m_PlayerShot.begin() + index);
	}
}

const std::vector<std::unique_ptr<PShot>>& PShotManager::GetPlayerShot() const
{
	return m_PlayerShot;
}

PShot* PShotManager::GetPlayrShot(size_t No)
{
	if (No < m_PlayerShot.size())
	{
		return m_PlayerShot[No].get();
	}
	return nullptr;
}

size_t PShotManager::GetPlayerShotCount() const
{
	return m_PlayerShot.size();
}