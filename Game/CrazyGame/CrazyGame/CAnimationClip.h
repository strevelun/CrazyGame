#pragma once

#include <vector>
#include <string>
#include "Setting.h"

class CBitmap;

class CAnimationClip
{
    std::wstring m_clipName;
    std::vector<tAnimationFrame*> m_vecFrame;
    std::vector<CBitmap*> m_vecBitmap;
    size_t m_frameIdx = 0;
    float m_frameTime = 0.0f;
    float m_frameTimeLimit = 0.0f;
    bool m_isLoop = true;

    tAnimationFrame* m_curFrame;
    D2D1_RECT_F* m_frameRect;

    //Bitmap* m_bitmap;
    //D2D1_Rect_F* m_frameRect;

public:
    CAnimationClip();
    CAnimationClip(const std::wstring& _str);
    CAnimationClip(const CAnimationClip& _animClip);

    tAnimationFrame* GetCurFrame() const { return m_vecFrame.at(m_frameIdx); }
    size_t GetNumOfFrame() const { return m_vecFrame.size(); }
    size_t GetCurFrameIdx() const { return m_frameIdx; }
    tAnimationFrame* GetFrame(u_int _idx) { return m_vecFrame.at(_idx); }
    void SetCurFrameIdx(u_int _idx) { m_frameIdx = _idx; }
    tAnimationFrame* GetFirstFrame() const { return m_vecFrame.at(0); }
    size_t GetFrameSize() const { return m_vecFrame.size(); }
    bool IsCurClipEnd() const { 
        int a = 1 + 1;
        return m_frameIdx >= m_vecFrame.size() - 1; 
    }

    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget, D2D1_RECT_F _rect);

    void AddFrame(tAnimationFrame* _frame);
    void SetFrametimeLimit(float _frameTimeLimit) { m_frameTimeLimit = _frameTimeLimit; }
    void SetLoop(bool _isLoop) { m_isLoop = _isLoop; }
};

