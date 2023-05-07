#pragma once
#include "CObj.h"
#include <d2d1.h>
class CUI :
    public CObj
{
public:
    CUI(const D2D1_RECT_F& _rect);
    ~CUI();

};

