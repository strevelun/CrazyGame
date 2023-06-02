#include "Stage.h"
#include "CTimer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CUIPanel.h"
#include "UIManager.h"

Stage::Stage()
{
	m_eState = eStageState::Ready;
	m_fPlayTime = 0.0f;

	m_uiManager = UIManager::GetInst();

	m_mapMoveObjCnt.insert(std::make_pair(MoveObjType::Player, 0));
	m_mapMoveObjCnt.insert(std::make_pair(MoveObjType::Boss, 0));
	m_mapMoveObjCnt.insert(std::make_pair(MoveObjType::Monster, 0));
}

Stage::~Stage()
{
}

void Stage::Update()
{
	m_fPlayTime += CTimer::GetInst()->GetDeltaTime();

	CheckState();
}

void Stage::CheckState()
{
	switch (m_eState)
	{
	case eStageState::Ready:
		if (m_fPlayTime >= 3.0f)
		{
			m_eState = eStageState::Play;
			m_uiManager->GetUIPanel()->SetAlive(false);
		}
		break;
	case eStageState::Play:
		if (m_fPlayTime >= 300.0f)
		{
			m_eState = eStageState::End;
			m_uiManager->ShowAndAddUIPanel(L"draw.png");
			m_fPlayTime = 0.0f;
		}
		else if (m_mapMoveObjCnt[MoveObjType::Boss] <= 0 && m_mapMoveObjCnt[MoveObjType::Monster] <= 0)
		{
			m_eState = eStageState::End;
			m_uiManager->ShowAndAddUIPanel(L"win.png");
			m_fPlayTime = 0.0f;
		}
		else if (m_mapMoveObjCnt[MoveObjType::Player] <= 0)
		{
			m_eState = eStageState::End;
			m_uiManager->ShowAndAddUIPanel(L"lose.png");
			m_fPlayTime = 0.0f;
		}
		break;
	case eStageState::End:
		if (m_fPlayTime >= 3.0f)
		{
			m_uiManager->GetUIPanel()->SetAlive(false);
			CSceneManager::GetInst()->ChangeScene(L"LobbyScene");
		}
		break;
	}
}

void Stage::Cleanup()
{
	m_mapMoveObjCnt.clear();
}
