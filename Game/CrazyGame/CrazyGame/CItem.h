#pragma once
#include "CStaticObj.h"
#include <string>

class CPlayer;

class CItem :
    public CStaticObj
{
    eItem m_eItem;
    std::wstring m_itemName;

public:
    CItem(const D2D1_RECT_F _rect, eInGameObjType _type);
    ~CItem();
    void Init(eItem _eItem, std::wstring _strName);
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void SetItemEnum(eItem _eItem) { m_eItem = _eItem; }
    void SetItemName(std::wstring _strName) { m_itemName = _strName; }
    void Benefit(CPlayer* _pPlayer);
    
    eItem GetItemEnum() { return m_eItem; }
    std::wstring GetItemName() { return m_itemName; }

    void Die() override;
};

