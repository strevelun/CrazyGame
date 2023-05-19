#pragma once
#include "CUI.h"

#include <functional>


class CUIButton :
    public CUI
{
    std::function<void(const std::wstring _strName)> m_BtnCallback;

public:
    CUIButton(const D2D1_RECT_F& _rect, std::wstring _strName);
    ~CUIButton();

    void Update() override;

    template <typename T>
    void SetCallback(T* pObj, void (T::* pFunc)(const std::wstring _strName))
    {
        m_BtnCallback = bind(pFunc, pObj, std::placeholders::_1);
    }
};

