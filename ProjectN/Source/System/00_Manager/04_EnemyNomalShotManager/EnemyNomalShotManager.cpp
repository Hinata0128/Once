#include "EnemyNomalShotManager.h"

EnemyNomalShotManager* EnemyNomalShotManager::m_pInstance = nullptr;

EnemyNomalShotManager::EnemyNomalShotManager()
{
}

EnemyNomalShotManager::~EnemyNomalShotManager()
{
}

EnemyNomalShotManager* EnemyNomalShotManager::GetInstance()
{
	static EnemyNomalShotManager s_Instance;
	return &s_Instance;
}

void EnemyNomalShotManager::Update()
{
	for (auto it = m_EnemyNomalShot.begin(); it != m_EnemyNomalShot.end();)
	{
		(*it)->Update();

		//¶‘¶‚µ‚Ä‚¢‚È‚¢’e‚Ííœ.
		if (!(*it)->IsActive())
		{
			it = m_EnemyNomalShot.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EnemyNomalShotManager::Draw()
{
	for (std::unique_ptr<EnemyNomalShot>& ENomalShot : m_EnemyNomalShot)
	{
		ENomalShot->Draw();
	}
}


void EnemyNomalShotManager::AddEnemyNomalShot(const D3DXVECTOR3& Pos, const D3DXVECTOR3& InitDirecton)
{
	//ƒ[ƒJƒ‹•Ï”‚Åspeed‚ğİ’è‚µ‚Ä‚¢‚Ü‚·.
	constexpr float Speed = 0.05f;

	auto ENomalShot = std::make_unique<EnemyNomalShot>();

	ENomalShot->Reload(Pos, InitDirecton, Speed);

	ENomalShot->SetDisplay(true);

	m_EnemyNomalShot.push_back(std::move(ENomalShot));
}

void EnemyNomalShotManager::ReMoveEnemyNomalShot(size_t index)
{
	if (index < m_EnemyNomalShot.size())
	{
		m_EnemyNomalShot.erase(m_EnemyNomalShot.begin() + index);
	}
}

const std::vector<std::unique_ptr<EnemyNomalShot>>& EnemyNomalShotManager::GetEnemyNomalShot() const
{
	return m_EnemyNomalShot;
}


EnemyNomalShot* EnemyNomalShotManager::GetEnemyNomalShot(size_t No)
{
	if (No < m_EnemyNomalShot.size())
	{
		return m_EnemyNomalShot[No].get();
	}
	return nullptr;
}

size_t EnemyNomalShotManager::GetEnemyNomalShotCount() const
{
	return m_EnemyNomalShot.size();
}