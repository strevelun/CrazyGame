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
	if (m_mouseState == eMouseState::Click)
		m_mouseState = eMouseState::None;
	else if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		m_mouseState = eMouseState::Press;
	else if (m_mouseState == eMouseState::Press)
		m_mouseState = eMouseState::Click;
}

void CMouse::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(CApp::GetInst()->GetHwnd(), &pt);
	m_point = D2D1::Point2F(pt.x, pt.y);
	
	if (pt.x < 0) pt.x = 0;
	if (pt.y < 0) pt.y = 0;

	m_rect.left = pt.x;
	m_rect.top = pt.y;
	m_rect.right = pt.x + m_size.width / 2;
	m_rect.bottom = pt.y + m_size.height;
}

void CMouse::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect, 
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF(0,0, m_size.width / 2, m_size.height));
}
