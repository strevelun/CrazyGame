#include "StageManager.h"
#include "Stage.h"

StageManager* StageManager::m_inst = nullptr;

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

void StageManager::ChangeStage(Stage* _stage)
{
	if (m_stage)	delete m_stage;
	m_stage = _stage;
}
