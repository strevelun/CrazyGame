#include "CMoveObj.h"
#include "CInGameScene.h"
#include "CBoard.h"
#include "CSceneManager.h"

CMoveObj::CMoveObj(const D2D1_RECT_F& _rect) : CObj(_rect)
{
}

CMoveObj::~CMoveObj()
{
}

void CMoveObj::MoveOnMoveObjBoard(eInGameObjType _type)
{
	auto scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();
	scene->m_board->SetObjTypeInMoveObjBoard(m_prevCellXPos, m_prevCellYPos, eInGameObjType::None);
	scene->m_board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, _type);
	m_prevCellXPos = m_cellXPos;
	m_prevCellYPos = m_cellYPos;
}
