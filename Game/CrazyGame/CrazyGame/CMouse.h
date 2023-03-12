#pragma once
#include "CObj.h"
class CMouse :
    public CObj
{
    D2D1_POINT_2F	m_point;

public:
    CMouse();
    ~CMouse();

    void Input() override;
    void Update() override;
    void Render(ID2D1RenderTarget* _pRenderTarget) override;
};

