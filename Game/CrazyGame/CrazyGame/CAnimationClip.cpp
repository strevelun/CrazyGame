#include "CAnimationClip.h"
#include "CTimer.h"
#include "CBitmap.h"
#include "CResourceManager.h"

CAnimationClip::CAnimationClip()
{
	m_clipName = L"";
}

CAnimationClip::CAnimationClip(const std::wstring& _str)
{
	m_clipName = _str;
}

CAnimationClip::CAnimationClip(const CAnimationClip& _animClip)
{
	m_clipName = _animClip.m_clipName;
	m_frameIdx = _animClip.m_frameIdx;
	m_frameTimeLimit = _animClip.m_frameTimeLimit;
	m_vecFrame = _animClip.m_vecFrame;
	m_isLoop = _animClip.m_isLoop;
	m_curFrame = _animClip.m_curFrame;
}

void CAnimationClip::Update()
{
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
	D2D1_RECT_F source = GetCurFrame()->rect;
	int width = source.right - source.left;
	int height = source.bottom - source.top;

	tAnimationFrame* current = GetCurFrame();
	D2D1_RECT_F target = { _rect.left, _rect.top,
			_rect.left + width, _rect.top + height };

	if (m_clipName.compare(L"bazzi_trap") == 0)
	{
		target.left -= 15;
		target.right -= 15;
		target.top -= 39;
		target.bottom -= 39;
	}
	else if (m_clipName.compare(L"bazzi_die") == 0)
	{
		target.left -= 11;
		target.right -= 11;
		target.top -= 60;
		target.bottom -= 60;
	}
	else if (m_clipName.compare(L"bazzi_ready") == 0)
	{
		target.top -= 10;
		target.bottom -= 10;
	}
		
	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(current->bitmapIdx)->GetBitmap(),
		target, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		current->rect);
}

void CAnimationClip::AddFrame(tAnimationFrame* _frame)
{
	m_vecFrame.push_back(_frame);
	//m_vecBitmap.push_back(CResourceManager::GetInst()->GetIdxBitmap(_frame->bitmapIdx));
}