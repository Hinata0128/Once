#include "Timer.h"

Timer::Timer()
	: m_DeltaTime	(0.0f)
	, m_lastTimer	(std::chrono::high_resolution_clock::now())
	, m_elapsedTime	(0.0f)
{
}

Timer::~Timer()
{
}

Timer& Timer::GetInstance()
{
	// TODO: return ステートメントをここに挿入します
	static Timer s_Instance;
	return s_Instance;

}

void Timer::Update()
{
	auto now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> diff = now - m_lastTimer;
	m_DeltaTime = diff.count();
	m_lastTimer = now;

	//経過時間を更新.
	m_elapsedTime += m_DeltaTime;
}

float Timer::DeltaTime() const
{
	return m_DeltaTime;
}

float Timer::ElapsedTime() const
{
	return m_elapsedTime;
}

