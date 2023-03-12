#pragma once

class CMouse;

class CInputManager
{
private:
	CMouse* m_pMouse;

	static CInputManager* m_inst;

	CInputManager();
	~CInputManager();

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

