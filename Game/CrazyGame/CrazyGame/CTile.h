#pragma once
#include "CStaticObj.h"
#include "Setting.h"
class CTile :
    public CStaticObj
{

public:
    CTile();
    ~CTile();

    void Render(ID2D1RenderTarget* _pRenderTarget);
};

