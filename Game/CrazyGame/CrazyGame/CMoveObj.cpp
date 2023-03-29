#include "CMoveObj.h"
#include "CInGameScene.h"
#include "CBoard.h"

CMoveObj::CMoveObj()
{
}

CMoveObj::~CMoveObj()
{
}

void CMoveObj::MoveOnMoveObjBoard()
{
	auto scene = dynamic_cast<CInGameScene*>(m_pScene);
	scene->m_board->SetObjTypeInMoveObjBoard(m_prevXPos, m_prevYPos, eInGameObjType::None);
	scene->m_board->SetObjTypeInMoveObjBoard(m_xpos, m_ypos, eInGameObjType::Character);
}
