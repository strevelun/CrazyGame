#pragma once

#include <Windows.h>

#pragma comment(lib, "Winmm.lib")

class CTimer
{
	static CTimer* m_inst;

	DWORD m_tick = 0;
	float m_deltaTime = 0;
	int m_frame = 0;
	float m_elapsedTime = 0;
	float m_fps = 0;
	int m_frameLimit = 0;
	float m_time = 0;

	CTimer();
	~CTimer();
public:
	static CTimer* GetInst()
	{
		if (m_inst == nullptr)  m_inst = new CTimer();
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst != nullptr)
		{
			delete m_inst;
			m_inst = nullptr;
		}
	}

	void SetFrameLimit(int _limit) { m_frameLimit = _limit; }

	float GetDeltaTime() const { return m_deltaTime; }
	bool Update();
};

