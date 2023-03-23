#pragma once
#include "CObj.h"
class CMoveObj :
    public CObj
{
protected:
    int m_xpos, m_ypos;
    int m_prevXPos, m_prevYPos;
    bool m_isDying = false;

public:
    CMoveObj();
    ~CMoveObj();

    void SetIsDying(bool _isDying) { m_isDying = _isDying; }
};

