#pragma once
#include "CObj.h"
#include <d2d1.h>
class CUI :
    public CObj
{
protected:
    CBitmap* m_pBitmap;

public:
    CUI();
    CUI(const D2D1_RECT_F& _rect);
    ~CUI();

    void SetBitmap(CBitmap* _bitmap);

    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
};

