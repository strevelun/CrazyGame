#pragma once
#include "CStaticObj.h"
#include <string>

class CItem :
    public CStaticObj
{
    std::string m_itemName;

public:
    CItem();
    ~CItem();
    void Render(ID2D1RenderTarget* _pRenderTarget);
    void SetItemName(std::string _itemName) { m_itemName = _itemName; }
};

