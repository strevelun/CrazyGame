#pragma once
#include "BubbleSkill.h"


enum class eThrowState
{
    None,
    InAir,
    Bounce
};

class BounceMoveSkill :
    public BubbleSkill
{
private:
    int m_throwLimit = 10;
    int m_curThrow = 0;
    float m_angle = 45.0f;
    float m_gravity = 9.8f;
    float m_ballTime = 0.0f;

    eThrowState m_eThrowState = eThrowState::None; // 좌우로 던질떄만

public:
    BounceMoveSkill(CBubble* _pOwner, eDir _eDir);
    virtual ~BounceMoveSkill();

    void Update() override;
};

