#include "CUI.h"
#include "CBitmap.h"

CUI::CUI()
{
}

CUI::CUI(const D2D1_RECT_F& _rect) : CObj(_rect)
{

}

CUI::~CUI()
{

}

void CUI::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	if (m_pBitmap == nullptr)
		return;

	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect);
}
