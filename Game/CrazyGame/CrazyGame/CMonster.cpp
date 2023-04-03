#include "CMonster.h"
#include "CBitmap.h"

CMonster::CMonster(const D2D1_RECT_F& _rect) : CMoveObj(_rect)
{
}

CMonster::~CMonster()
{
}

void CMonster::Render(ID2D1RenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_sprite->rect);
}
