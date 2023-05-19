#pragma once

#include <list>
#include <map>

enum class MoveObjType
{
	Player,
	Monster,
	Boss
};

enum class eStageState
{
	Ready,
	Play,
	End
};

class CInGameScene;
class UIManager;

class Stage
{
private:
	UIManager* m_uiManager;

	std::map<MoveObjType, int> m_mapMoveObjCnt;
	eStageState  m_eState;

	float m_fPlayTime;

public:
	Stage();
	~Stage();

	void Update();
	void CheckState();

	eStageState GetStageState() const { return m_eState; }
	void SetStageState(eStageState _state) { m_eState = _state; }

	void AddMoveObjCnt(MoveObjType _type) { m_mapMoveObjCnt.at(_type)++; }
	void SubMoveObjCnt(MoveObjType _type) { m_mapMoveObjCnt.at(_type)--; }

	void Cleanup();
};

