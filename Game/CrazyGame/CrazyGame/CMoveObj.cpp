#include "CMoveObj.h"
#include "CInGameScene.h"
#include "CBoard.h"

CMoveObj::CMoveObj(const D2D1_RECT_F& _rect) : CObj(_rect)
{
}

CMoveObj::~CMoveObj()
{
}

void CMoveObj::MoveOnMoveObjBoard(eInGameObjType _type)
{
	auto scene = dynamic_cast<CInGameScene*>(m_pScene);
	scene->m_board->SetObjTypeInMoveObjBoard(m_prevCellXPos, m_prevCellYPos, eInGameObjType::None);
	scene->m_board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, _type);
	m_prevCellXPos = m_cellXPos;
	m_prevCellYPos = m_cellYPos;
}
