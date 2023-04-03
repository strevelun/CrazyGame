#pragma once
#include "CMoveObj.h"
class CMonster :
    public CMoveObj
{
public:
    CMonster(const D2D1_RECT_F& _rect);
    ~CMonster();
    void Render(ID2D1RenderTarget* _pRenderTarget);
};

