#include "CGameObj.h"

CGameObj::CGameObj(const D2D1_RECT_F& _rect) : CObj(_rect)
{

	m_xpos = _rect.left;
	m_ypos = _rect.bottom - (BOARD_BLOCK_SIZE / 2);

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	m_cellXPos = (m_xpos - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = (m_ypos - stageFrameOffsetY) / BOARD_BLOCK_SIZE;
}

CGameObj::~CGameObj()
{
}

void CGameObj::Update()
{
	m_anim.Update();
}
