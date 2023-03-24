#pragma once
#include "CObj.h"
class CStaticObj :
    public CObj
{
    u_int m_bitmapIdx;

public:
    void SetBitmapIdx(u_int _bitmapIdx) { m_bitmapIdx = _bitmapIdx; }
};

