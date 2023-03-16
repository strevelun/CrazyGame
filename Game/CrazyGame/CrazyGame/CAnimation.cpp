#include "CAnimation.h"

CAnimation::CAnimation()
{
	m_idx = 0;
}

CAnimation::~CAnimation()
{
}

void CAnimation::AddClip(tAnimationClip* _clip)
{
	m_vecClip.push_back(_clip);
}

void CAnimation::Update()
{
	m_curClip = m_vecClip[m_idx++ % m_vecClip.size()];
}
