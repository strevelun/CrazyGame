#pragma once
#include "CObj.h"

class CAnimation;

class CBubble :
    public CObj
{
    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 3;

public:
    CBubble();
    ~CBubble();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);

    void Die() override;

};

