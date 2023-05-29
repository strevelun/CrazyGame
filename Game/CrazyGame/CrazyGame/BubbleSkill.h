#pragma once
#include "Skill.h"

class CBubble;

class BubbleSkill :
    public Skill
{
protected:
    eDir m_eMovingDir = eDir::None;
    int m_dirX, m_dirY;

    D2D1_POINT_2U m_prevCellPos = {};

public:
    BubbleSkill(eDir _eDir);
    virtual ~BubbleSkill();
    virtual void Update();
};

