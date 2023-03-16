#pragma once

#include "Setting.h"

#include <vector>

class CAnimation
{
	std::vector<tAnimationClip*> m_vecClip;
	tAnimationClip* m_curClip;
	bool m_bLoop = false;
	int m_idx;

public:
	CAnimation();
	~CAnimation();
	void AddClip(tAnimationClip* _clip);
	tAnimationClip* GetCurClip() const { return m_curClip; }

	void Update();
};

