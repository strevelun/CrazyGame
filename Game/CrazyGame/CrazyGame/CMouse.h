#pragma once
#include "CUI.h"

enum class eMouseState
{
    None,
    Press,
    Click
};

class CMouse :
    public CUI
{
    D2D1_POINT_2F	m_point;
    bool m_isPressed = false;
    eMouseState m_mouseState = eMouseState::None;

public:
    CMouse();
    ~CMouse();

    void Input() override;
    void Update() override;
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget) override;

    eMouseState GetMouseState() const { return m_mouseState; }
    D2D1_POINT_2F GetMousePoint() const { return m_point; }
};

