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

class CAnimator
{
	std::map<std::wstring, CAnimationClip*> m_mapClip;
	CAnimationClip* m_curClip;
	std::wstring m_strCurClipName;

public:
	CAnimator();
	~CAnimator();
	void AddClip(std::wstring _strClipName, CAnimationClip* _clip);
	void SetClip(std::wstring _strClipName);
	CAnimationClip* GetClip(std::wstring _strClipName) const;
	CAnimationClip* GetCurClip() const { return m_curClip; }

	void Update();
	void Render(ID2D1BitmapRenderTarget* _pRenderTarget, D2D1_RECT_F _rect);
};

