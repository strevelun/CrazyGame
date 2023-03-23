#pragma once
#include "CMoveObj.h"
class CMonster :
    public CMoveObj
{
public:
    CMonster();
    ~CMonster();
    void Render(ID2D1RenderTarget* _pRenderTarget);
};

