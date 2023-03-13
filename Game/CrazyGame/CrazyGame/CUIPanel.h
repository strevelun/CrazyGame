#pragma once

#include "CUI.h"

class CUIPanel :
    public CUI
{
public:
    CUIPanel();
    ~CUIPanel();

    void Render(ID2D1RenderTarget* _pRenderTarget);
};

