#include "CTimer.h"
#include <iostream>

CTimer* CTimer::m_inst = nullptr;

CTimer::CTimer()
{
	m_tick = timeGetTime();
}

CTimer::~CTimer()
{
}

bool CTimer::Update()
{
	DWORD tick = timeGetTime();

	m_deltaTime = (float)(tick - m_tick) / 1000;
	m_time += m_deltaTime;
	m_tick = tick;

#ifdef _DEBUG
	char str[50] = "";
	sprintf_s(str, "%f\n", m_deltaTime);
	OutputDebugStringA(str);
#endif

	m_elapsedTime += m_deltaTime;
	if (m_frameLimit > 0)
		if (m_time < (1.0f / m_frameLimit))
		{
			// frameLimit이 클수록 Logic을 실행하는 빈도가 늘어나서 deltaTime이 느려진다.
			return false; // frameLimit 분의 1로 나눠서 1초 안에 frameLimit번 만큼만 로직을 돌도록
		}

	m_time = 0;
	m_frame++;

	if (m_elapsedTime >= 1.0f)
	{
		m_fps = m_frame / m_elapsedTime;
		m_frame = 0;
		m_elapsedTime = 0;
	}
	return true;
}
