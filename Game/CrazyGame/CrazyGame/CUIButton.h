#pragma once
#include "CUI.h"

#include <functional>


class CUIButton :
    public CUI
{
    std::function<void(const std::string _strName)> m_BtnCallback;

public:
    CUIButton(std::string _strName);
    ~CUIButton();

    void Input() override;

    template <typename T>
    void SetCallback(T* pObj, void (T::* pFunc)(const std::string _strName))
    {
        m_BtnCallback = bind(pFunc, pObj,std::placeholders::_1);
    }
};

