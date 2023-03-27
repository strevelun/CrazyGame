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
	if (m_prevXPos != m_xpos || m_prevYPos != m_ypos)
	{
		auto scene = dynamic_cast<CInGameScene*>(m_pScene);
		scene->m_board->SetObjTypeInMoveObjBoard(m_prevXPos, m_prevYPos, eInGameObjType::None);
		scene->m_board->SetObjTypeInMoveObjBoard(m_xpos, m_ypos, eInGameObjType::Character);
	}
}
