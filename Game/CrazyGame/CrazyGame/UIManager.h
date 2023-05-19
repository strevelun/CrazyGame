#pragma once
#include "Setting.h"

class CUIPanel;

class UIManager
{
	static UIManager* m_inst;

	CUIPanel* m_statePanel;

	UIManager();
	~UIManager();

public:
	static UIManager* GetInst()
	{
		if (m_inst == nullptr) m_inst = new UIManager;
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst != nullptr) { delete m_inst;	m_inst = nullptr; }
	}

	void SetUIPanel(CUIPanel* _panel) { m_statePanel = _panel; }
	CUIPanel* GetUIPanel() { return m_statePanel; }

	void ShowAndAddUIPanel(PCWSTR _strFileName);
};

