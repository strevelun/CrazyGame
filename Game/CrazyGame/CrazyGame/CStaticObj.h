#pragma once
#include "CObj.h"
#include <d2d1.h>

class CStaticObj :
    public CObj
{
    u_int m_bitmapIdx;

public:
    CStaticObj(const D2D1_RECT_F& _rect);
    ~CStaticObj();

    void SetBitmapIdx(u_int _bitmapIdx) { m_bitmapIdx = _bitmapIdx; }
};

