#pragma once
#include "CObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

class CBubble :
    public CObj
{
    CAnimator           m_animator;
    CAnimationClip      m_animClip;

    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 3;

public:
    CBubble(const D2D1_RECT_F& _rect);
    ~CBubble();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);

    void Die() override;

};
