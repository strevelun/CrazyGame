#include "CObj.h"
#include "CBitmap.h"
#include "CResourceManager.h"

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
	//if (m_pBitmap == nullptr)
	//	return;

	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect);
}
