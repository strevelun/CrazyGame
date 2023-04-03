#pragma once
#include "CObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

#include <string>

class CSplash :
    public CObj
{
    CAnimator           m_animator;
    CAnimationClip      m_animClip;

public:
    CSplash(const D2D1_RECT_F& _rect, std::string _animClipName);
    ~CSplash();

    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);
};

