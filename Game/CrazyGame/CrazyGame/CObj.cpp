#include "CObj.h"
#include "CBitmap.h"

CObj::CObj()
{
}

CObj::~CObj()
{
}

void CObj::Input()
{
}

void CObj::Update()
{
}

void CObj::Render(ID2D1RenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect);
}
