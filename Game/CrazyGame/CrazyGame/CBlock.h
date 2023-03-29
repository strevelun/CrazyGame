#pragma once
#include "CStaticObj.h"

class CItem;

class CBlock :
    public CStaticObj
{
    CItem* m_pItem = nullptr;

public:
    CBlock();
    ~CBlock();

    void Render(ID2D1RenderTarget* _pRenderTarget);

    void Die() override;
};

