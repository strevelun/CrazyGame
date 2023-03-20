#pragma once

#include "Setting.h"

#include <vector>
#include <string>
#include <map>

class CAnimationClip;

/*
struct FRAME
{
	CSprite*	sprite;
	float		elapsedTime;
};
*/

class CAnimation
{
	std::map<std::string, CAnimationClip*> m_mapClip;
	CAnimationClip* m_curClip;

public:
	CAnimation();
	~CAnimation();
	void AddClip(std::string _strClipName, CAnimationClip* _clip);
	void SetClip(std::string _strClipName);
	CAnimationClip* GetClip(std::string _strClipName) const;
	CAnimationClip* GetCurClip() const { return m_curClip; }

	void Update();
};

