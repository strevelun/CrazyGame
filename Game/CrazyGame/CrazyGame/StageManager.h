#pragma once

class Stage;

class StageManager
{
private:
	static StageManager* m_inst;
	StageManager();
	~StageManager();

	Stage* m_stage;

public:
	static StageManager* GetInst()
	{
		if (m_inst == nullptr) m_inst = new StageManager;
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst != nullptr) { delete m_inst;	m_inst = nullptr; }
	}

	void ChangeStage(Stage* _stage);
	Stage* GetStage() const { return m_stage; }
};

