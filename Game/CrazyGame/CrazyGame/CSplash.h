#pragma once
#include "CStaticObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

#include <string>

class CSplash :
    public CStaticObj
{
public:
    CSplash(const D2D1_RECT_F& _rect, std::wstring _animClipName);
    ~CSplash();

    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
};

