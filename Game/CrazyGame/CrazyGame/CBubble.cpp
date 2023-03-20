#include "CBubble.h"
#include "CAnimation.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CAnimationClip.h"

CBubble::CBubble()
{
}

CBubble::~CBubble()
{
}

void CBubble::Update()
{
	CObj::Update();
	m_elapsedTime += CTimer::GetInst()->GetDeltaTime();
	if (m_elapsedTime >= m_dieTime)
	{

		m_isAlive = false;
	}
}

void CBubble::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = m_pAnim->GetClip("bubble");
	if (!clip) return;
	tAnimationFrame* frame = clip->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->idx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}
 