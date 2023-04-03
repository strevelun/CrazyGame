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
	scene->m_board->SetObjTypeInMoveObjBoard(m_prevXPos, m_prevYPos, eInGameObjType::None);
	scene->m_board->SetObjTypeInMoveObjBoard(m_xpos, m_ypos, _type);
	m_prevXPos = m_xpos;
	m_prevYPos = m_ypos;
}
