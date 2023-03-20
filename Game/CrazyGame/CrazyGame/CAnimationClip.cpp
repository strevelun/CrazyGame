#include "CAnimationClip.h"
#include "CTimer.h"

CAnimationClip::CAnimationClip()
{
}

CAnimationClip::CAnimationClip(const CAnimationClip& _animClip)
{
	m_frameIdx = _animClip.m_frameIdx;
	m_frameTime = _animClip.m_frameTime;
	m_frameTimeLimit = _animClip.m_frameTimeLimit;
	m_vecFrame = _animClip.m_vecFrame;
}

void CAnimationClip::Update()
{
	m_frameTime += CTimer::GetInst()->GetDeltaTime();
	if (m_frameTime >= m_frameTimeLimit)
	{
		m_frameIdx = ++m_frameIdx % m_vecFrame.size();
		m_frameTime = 0.0f;
	}
}
