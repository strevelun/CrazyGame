#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

CItem::CItem(const D2D1_RECT_F _rect) : CStaticObj(_rect)
{

}

CItem::~CItem()
{
}

void CItem::Init(eItem _eItem, std::string _strName)
{
	CAnimator* anim = new CAnimator();
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(_strName);
	animClip->SetFrametimeLimit(0.2f);
	anim->AddClip(_strName, animClip);
	anim->SetClip(_strName);
	SetAnimation(anim);
	SetItemName(_strName);
	SetItemEnum((eItem)_eItem);
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
