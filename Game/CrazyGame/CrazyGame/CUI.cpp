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
	if (!m_pBitmap) return; // ºó²®µ¥±â UIÀÎ °æ¿ì (ex. backButton)

	m_pBitmap->SubRefCnt();
	if (m_pBitmap->GetRefCnt() == 0)
		delete m_pBitmap;

	//m_pBitmap->Release();
}

void CUI::SetBitmap(CBitmap* _bitmap)
{
	_bitmap->AddRefCnt();
	m_pBitmap = _bitmap;
}

void CUI::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	if (m_pBitmap == nullptr)
		return;

	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect);
}
