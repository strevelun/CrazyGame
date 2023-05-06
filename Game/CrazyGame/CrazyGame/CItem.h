#pragma once
#include "CStaticObj.h"
#include <string>

class CItem :
    public CStaticObj
{
    eItem m_eItem;
    std::string m_itemName;

public:
    CItem(const D2D1_RECT_F _rect, eInGameObjType _type);
    ~CItem();
    void Init(eItem _eItem, std::string _strName);
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void SetItemEnum(eItem _eItem) { m_eItem = _eItem; }
    void SetItemName(std::string _strName) { m_itemName = _strName; }
    
    eItem GetItemEnum() { return m_eItem; }
    std::string GetItemName() { return m_itemName; }

    void Die() override;
};

