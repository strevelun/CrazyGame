#pragma once

#include "CUI.h"

class CUIPanel :
    public CUI
{
public:
    CUIPanel(const D2D1_RECT_F& _rect);
    ~CUIPanel();

    void Render(ID2D1RenderTarget* _pRenderTarget);
};

