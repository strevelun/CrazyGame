#pragma once
#include "CStaticObj.h"
#include "Setting.h"
class CTile :
    public CStaticObj
{

public:
    CTile(const D2D1_RECT_F& _rect);
    ~CTile();

    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
};

