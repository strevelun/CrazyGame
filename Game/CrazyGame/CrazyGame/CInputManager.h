#pragma once

#include <map>
#include <functional>
#include <string>

class CMouse;
class CPlayer;

class CInputManager
{
private:
	float m_startTime, m_delayedTime;

	//std::map<std::wstring, std::function<void()>> m_mapAction;
	CMouse* m_pMouse;
	//CPlayer* m_pPlayer;

	static CInputManager* m_inst;

	CInputManager();
	~CInputManager();

private:
	//void SpaceBar();
	//void DoubleSpaceBar();

public:
	static CInputManager* GetInst()
	{
		if (m_inst == nullptr) m_inst = new CInputManager;
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst != nullptr) { delete m_inst;	m_inst = nullptr; }
	}

	CMouse* GetMouse() const { return m_pMouse; }

	void Input();
};

