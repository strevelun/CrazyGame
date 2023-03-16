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
			// frameLimit�� Ŭ���� Logic�� �����ϴ� �󵵰� �þ�� deltaTime�� ��������.
			return false; // frameLimit ���� 1�� ������ 1�� �ȿ� frameLimit�� ��ŭ�� ������ ������
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
