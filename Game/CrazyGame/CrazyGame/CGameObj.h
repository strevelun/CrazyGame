#pragma once
#include "CObj.h"

#include "CAnimator.h"
#include "CAnimationClip.h"

class CGameObj :
    public CObj
{
public:
    float m_xpos, m_ypos;

    CAnimator           m_anim;
    CAnimationClip      m_animClip;

public:
    CGameObj(const D2D1_RECT_F& _rect);
    ~CGameObj();

    void Update() override;
};

