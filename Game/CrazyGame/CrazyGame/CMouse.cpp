#include "CMouse.h"
#include "../../D2DCore/CApp.h"
#include "CBitmap.h"
#include "CResourceManager.h"

CMouse::CMouse()
{
	POINT pt;
	ShowCursor(false);
	GetCursorPos(&pt);
	ScreenToClient(CApp::GetInst()->GetHwnd(), &pt);

	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"mouse.png");
	m_size = bitmap->GetBitmap()->GetPixelSize();
	m_rect = D2D1::RectF(0, 0, m_size.width, m_size.height);
	SetBitmap(bitmap);
}

CMouse::~CMouse()
{
}

void CMouse::Input()
{

}

void CMouse::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(CApp::GetInst()->GetHwnd(), &pt);
	m_point = D2D1::Point2F(pt.x, pt.y);
	m_rect.left = pt.x;
	m_rect.top = pt.y;
	m_rect.right = pt.x + m_size.width / 2;
	m_rect.bottom = pt.y + m_size.height;
}

void CMouse::Render(ID2D1RenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect, 
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0,0, m_size.width / 2, m_size.height));
}
