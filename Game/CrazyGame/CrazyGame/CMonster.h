#pragma once
#include "CObj.h"
class CMonster :
    public CObj
{
public:
    CMonster();
    ~CMonster();
    void Render(ID2D1RenderTarget* _pRenderTarget);
};

