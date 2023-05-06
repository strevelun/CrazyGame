#include "CAnimator.h"
#include "CAnimationClip.h"

CAnimator::CAnimator()
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::AddClip(std::string _strClipName, CAnimationClip* _clip)
{
	m_mapClip.insert(std::make_pair(_strClipName, _clip));
}

void CAnimator::SetClip(std::string _strClipName)
{
	std::map<std::string, CAnimationClip*>::iterator iter = m_mapClip.find(_strClipName);
	if (iter == m_mapClip.end())
		return;

	m_curClip = iter->second;
	m_curClip->SetCurFrameIdx(0);
}

CAnimationClip* CAnimator::GetClip(std::string _strClipName) const
{
	if (_strClipName.compare(m_strCurClipName) == 0) return m_curClip;

	std::map<std::string, CAnimationClip*>::const_iterator iter = m_mapClip.find(_strClipName);
	if (iter == m_mapClip.end())
		return nullptr;

	return iter->second;
}

void CAnimator::Update()
{
	if (m_curClip == nullptr) return;
	m_curClip->Update();
}

void CAnimator::Render(ID2D1BitmapRenderTarget* _pRenderTarget, D2D1_RECT_F _rect)
{
	if (m_curClip == nullptr) return;
	m_curClip->Render(_pRenderTarget, _rect);
}