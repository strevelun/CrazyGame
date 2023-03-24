#pragma once
#include "CStaticObj.h"
class CItem :
    public CStaticObj
{
public:
    void Render(ID2D1RenderTarget* _pRenderTarget);
};

