#pragma once
#include "CStaticObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

#include <string>

class CMoveObj;

class CSplash :
    public CStaticObj
{
private:
    CMoveObj* m_pOwner = nullptr;

public:
    CSplash(const D2D1_RECT_F& _rect, std::wstring _animClipName, CMoveObj* _pOwner);
    ~CSplash();

    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
};

