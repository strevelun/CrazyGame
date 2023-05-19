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

    int m_cellXPos, m_cellYPos;
    int m_prevCellXPos, m_prevCellYPos;

public:
    CGameObj(const D2D1_RECT_F& _rect);
    ~CGameObj();

    void Update() override;
    D2D1_POINT_2U GetPoint() const { return D2D1::Point2U(m_cellXPos, m_cellYPos); }
};

