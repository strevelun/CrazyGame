#pragma once

#include "CUI.h"

class CUIPanel :
    public CUI
{
public:
    CUIPanel(const D2D1_RECT_F& _rect);
    ~CUIPanel();

    void SetRect(const D2D1_RECT_F& _rect) { m_rect = _rect; }

    void Render(ID2D1BitmapRenderTarget* _pRenderTarget) override;
};

