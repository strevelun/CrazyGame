#pragma once
#include "CObj.h"
#include "Setting.h"

class CPlayer :
    public CObj
{


public:
    CPlayer();
    ~CPlayer();

    void Render(ID2D1RenderTarget* _pRenderTarget);
};

