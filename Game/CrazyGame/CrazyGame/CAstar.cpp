#include "CAStar.h"
#include "CBoard.h"

CAStar::CAStar()
{

}

CAStar::~CAStar()
{

}

void CAStar::Init(CBoard* _board)
{
	tMapData mapData = _board->GetMapData();

	m_board.resize(mapData.gridY);
	for (u_int i = 0; i < mapData.gridY; i++)
		m_board[i].resize(mapData.gridX);
}