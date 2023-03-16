#include "CBubble.h"
#include "CAnimation.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"

CBubble::CBubble()
{
}

CBubble::~CBubble()
{
}

void CBubble::Update()
{
	m_anim->Update();
}

void CBubble::Render(ID2D1RenderTarget* _pRenderTarget)
{
	tAnimationClip* clip = m_anim->GetCurClip();
	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(clip->idx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		clip->rect);
}
