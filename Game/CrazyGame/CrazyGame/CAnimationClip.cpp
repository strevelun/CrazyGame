#include "CAnimationClip.h"
#include "CTimer.h"
#include "CBitmap.h"
#include "CResourceManager.h"

CAnimationClip::CAnimationClip()
{
}

CAnimationClip::CAnimationClip(const CAnimationClip& _animClip)
{
	m_frameIdx = _animClip.m_frameIdx;
	m_frameTimeLimit = _animClip.m_frameTimeLimit;
	m_vecFrame = _animClip.m_vecFrame;
	m_isLoop = _animClip.m_isLoop;
	m_curFrame = _animClip.m_curFrame;
}

void CAnimationClip::Update()
{
	CAnimationClip* temp = this;

	m_frameTime += CTimer::GetInst()->GetDeltaTime();
	if (m_frameTime >= m_frameTimeLimit)
	{
		if (IsCurClipEnd() && !m_isLoop)
		{
			m_frameIdx = 0;
			m_curFrame = m_vecFrame.at(m_frameIdx);
			return;
		}
		m_frameIdx = ++m_frameIdx % m_vecFrame.size();
		m_curFrame = m_vecFrame.at(m_frameIdx);
		m_frameTime = 0.0f;
	}
}

void CAnimationClip::Render(ID2D1BitmapRenderTarget* _pRenderTarget, D2D1_RECT_F _rect)
{
	tAnimationFrame* current = GetCurFrame();
	D2D1_RECT_F source = GetCurFrame()->rect;
	D2D1_RECT_F target = { _rect.left, _rect.top,
		_rect.left + (source.right - source.left), _rect.top + (source.bottom - source.top) };


	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(current->bitmapIdx)->GetBitmap(),
		target, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		current->rect);

	/*
	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(GetCurFrame()->bitmapIdx)->GetBitmap(),
		_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		GetCurFrame()->rect);
		*/
	//_pRenderTarget->DrawBitmap(m_vecBitmap[m_curFrame->bitmapIdx]->GetBitmap(),
	//		_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//		m_curFrame->rect);
}

void CAnimationClip::AddFrame(tAnimationFrame* _frame)
{
	m_vecFrame.push_back(_frame);
	//m_vecBitmap.push_back(CResourceManager::GetInst()->GetIdxBitmap(_frame->bitmapIdx));
}