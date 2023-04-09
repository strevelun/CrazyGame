#include "CObj.h"
#include "CBitmap.h"
#include "CResourceManager.h"
#include "CAnimator.h"

CObj::CObj()
{
}

CObj::CObj(const D2D1_RECT_F& _rect)
{
	m_rect = _rect;
	CObj::RectToPos(_rect, m_cellXPos, m_cellYPos);
	m_prevCellXPos = m_cellXPos;
	m_prevCellYPos = m_cellYPos;
}

CObj::~CObj()
{
}

void CObj::RectToPos(D2D1_RECT_F _rect, int& _x, int& _y)
{
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = _rect.left - stageFrameOffsetX + BOARD_BLOCK_SIZE / 2;
	int top = _rect.top - stageFrameOffsetY + BOARD_BLOCK_SIZE / 2;

	_x = left / BOARD_BLOCK_SIZE;
	_y = top / BOARD_BLOCK_SIZE;
}

void CObj::Input()
{
}

void CObj::Update()
{
	if (!m_pAnim) return;

	m_pAnim->Update();
}

void CObj::Render(ID2D1RenderTarget* _pRenderTarget)
{
	if (m_pBitmap == nullptr)
		return;

	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect);
}

void CObj::Die()
{
}
