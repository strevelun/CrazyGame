#pragma once
#include "CObj.h"

class CAnimation;

class CBubble :
    public CObj
{
    CAnimation* m_anim;

public:
    CBubble();
    ~CBubble();
    void SetAnimation(CAnimation* _anim) { if (m_anim) delete m_anim; m_anim = _anim; }
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);
};

