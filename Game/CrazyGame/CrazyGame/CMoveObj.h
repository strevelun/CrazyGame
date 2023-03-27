#pragma once
#include "CObj.h"
class CMoveObj :
    public CObj
{
protected:
    bool m_isDying = false;

public:
    CMoveObj();
    ~CMoveObj();

    void SetIsDying(bool _isDying) { m_isDying = _isDying; }
};

