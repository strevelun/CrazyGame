#pragma once
#include "CGameObj.h"
#include <d2d1.h>

class CStaticObj :
    public CGameObj
{
    u_int m_bitmapIdx;

protected:
    tSprite* m_sprite;

public:
    CStaticObj(const D2D1_RECT_F& _rect);
    ~CStaticObj();

    void SetBitmapIdx(u_int _bitmapIdx) { m_bitmapIdx = _bitmapIdx; }
    void SetSprite(tSprite* _sprite) { m_sprite = _sprite; }

    u_int GetBitmapIdx() const { return m_bitmapIdx; }
};

