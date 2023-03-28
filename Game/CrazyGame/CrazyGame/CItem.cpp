#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = m_pAnim->GetClip(m_itemName);
	if (!clip) return;
	tAnimationFrame* frame = clip->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}

void CItem::Die()
{
	m_isAlive = false;
}
