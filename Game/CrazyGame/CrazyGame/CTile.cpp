#include "CTile.h"
#include "CResourceManager.h"
#include "CBitmap.h"

CTile::CTile(const D2D1_RECT_F& _rect) : CStaticObj(_rect)
{
}

CTile::~CTile()
{
}

void CTile::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	D2D1_RECT_F source = m_sprite->rect;
	D2D1_RECT_F target = { m_rect.left, m_rect.top,
	m_rect.left + 40, m_rect.top + 40 };

	_pRenderTarget->DrawBitmap(
		CResourceManager::GetInst()->GetIdxBitmap(m_sprite->idx)->GetBitmap(),
		target, //m_rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_sprite->rect);
}
