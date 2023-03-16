#pragma once
#include "CObj.h"
#include "Setting.h"
class CTile :
    public CObj
{
    eType m_type;
    u_int m_bitmapIdx;

public:
    CTile();
    ~CTile();

    void Render(ID2D1RenderTarget* _pRenderTarget);
    void SetBitmapIdx(u_int _bitmapIdx) { m_bitmapIdx = _bitmapIdx; }
    //void SetType(eType _type) { m_type = _type; }
};

