#pragma once
#include "CObj.h"
#include <string>

class CSplash :
    public CObj
{
    std::string m_clipName;

public:
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);

    void SetClipName(std::string _clipName) { m_clipName = _clipName; }
};

