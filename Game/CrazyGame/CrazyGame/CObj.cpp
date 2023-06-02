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
	m_size.width = _rect.right - _rect.left;
	m_size.height = _rect.bottom - _rect.top;
}

CObj::~CObj()
{
}

void CObj::RectToPos(D2D1_RECT_F _rect, int& _x, int& _y)
{
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40 ;
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
}

void CObj::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{

}

void CObj::Die()
{
}
