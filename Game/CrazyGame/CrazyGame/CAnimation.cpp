#include "CAnimation.h"
#include "CAnimationClip.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::AddClip(std::string _strClipName, CAnimationClip* _clip)
{
	m_mapClip.insert(std::make_pair(_strClipName, _clip));
}

void CAnimation::SetClip(std::string _strClipName)
{
	std::map<std::string, CAnimationClip*>::iterator iter = m_mapClip.find(_strClipName);
	if (iter == m_mapClip.end())
		return;

	m_curClip = iter->second;
}

CAnimationClip* CAnimation::GetClip(std::string _strClipName) const
{
	std::map<std::string, CAnimationClip*>::const_iterator iter = m_mapClip.find(_strClipName);
	if (iter == m_mapClip.end())
		return nullptr;

	return iter->second;
}

void CAnimation::Update()
{
	if (m_curClip == nullptr) return;
	m_curClip->Update();
}
