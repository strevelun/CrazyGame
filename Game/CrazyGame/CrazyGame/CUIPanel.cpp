#include "CUIPanel.h"

CUIPanel::CUIPanel(const D2D1_RECT_F& _rect) : CUI(_rect)
{
}

CUIPanel::~CUIPanel()
{
}

void CUIPanel::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	CObj::Render(_pRenderTarget);
}
