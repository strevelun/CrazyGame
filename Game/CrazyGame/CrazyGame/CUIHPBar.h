#pragma once
#include "CUI.h"
class CUIHPBar :
    public CUI
{
    u_int m_maxHp, m_hp;
    class CUIPanel* m_background;

public:
    CUIHPBar(CBitmap* _backBitmap, CBitmap* _gaugeBitmap, const D2D1_RECT_F& _rect, u_int _maxHp);
    CUIHPBar(const D2D1_RECT_F& _rect, u_int _maxHp);
    ~CUIHPBar();

    void SetHP(u_int _hp) { m_hp = _hp; }
    void SetRect(D2D1_RECT_F _rect);

    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

    void Die() override;
};

