#include "CTile.h"
#include "CResourceManager.h"
#include "CBitmap.h"

CTile::CTile(const D2D1_RECT_F& _rect) : CStaticObj(_rect)
{
}

CTile::~CTile()
{
}

void CTile::Render(ID2D1RenderTarget* _pRenderTarget)
{

	_pRenderTarget->DrawBitmap(
		CResourceManager::GetInst()->GetIdxBitmap(m_sprite->idx)->GetBitmap(),
		m_rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_sprite->rect);
}
