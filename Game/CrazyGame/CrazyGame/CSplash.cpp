#include "CSplash.h"
#include "CAnimationClip.h"
#include "CResourceManager.h"
#include "CAnimation.h"
#include "CBitmap.h"

void CSplash::Update()
{
	CObj::Update();
	CAnimationClip* clip = m_pAnim->GetCurClip();

	if (clip->GetNumOfFrame() - 1 <= clip->GetCurFrameIdx())
		m_isAlive = false;
}

void CSplash::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = m_pAnim->GetClip(m_clipName);
	if (!clip) return;
	tAnimationFrame* frame = clip->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->idx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}
