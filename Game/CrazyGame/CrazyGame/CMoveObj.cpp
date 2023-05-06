#include "CMoveObj.h"
#include "CInGameScene.h"
#include "CBoard.h"
#include "CSceneManager.h"
#include "CAnimator.h"

CMoveObj::CMoveObj(const D2D1_RECT_F& _rect) : CObj(_rect)
{
}

CMoveObj::~CMoveObj()
{
}

void CMoveObj::MoveOnMoveObjBoard(CMoveObj* _obj)
{
	auto scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();
	scene->m_board->SetObjTypeInMoveObjBoard(m_prevCellXPos, m_prevCellYPos, nullptr);
	scene->m_board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, _obj);
	m_prevCellXPos = m_cellXPos;
	m_prevCellYPos = m_cellYPos;
}

void CMoveObj::ChangeState(State _state)
{
}
