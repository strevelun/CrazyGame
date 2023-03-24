#pragma once

#include <vector>
#include "Setting.h"

class CAnimationClip
{
    std::vector<tAnimationFrame*> m_vecFrame;
    size_t m_frameIdx = 0;
    float m_frameTime = 0.0f;
    float m_frameTimeLimit = 0.0f;
    bool m_isLoop = true;

public:
    CAnimationClip();
    CAnimationClip(const CAnimationClip& _animClip);

    tAnimationFrame* GetCurFrame() const { return m_vecFrame.at(m_frameIdx); }
    size_t GetNumOfFrame() const { return m_vecFrame.size(); }
    size_t GetCurFrameIdx() const { return m_frameIdx; }
    tAnimationFrame* GetFirstFrame() const { return m_vecFrame.at(0); }
    size_t GetFrameSize() const { return m_vecFrame.size(); }
    bool IsCurClipEnd() const { return m_frameIdx >= m_vecFrame.size() - 1; }

    void Update();
    void AddFrame(tAnimationFrame* _frame) { m_vecFrame.push_back(_frame); }
    void SetFrametimeLimit(float _frameTimeLimit) { m_frameTimeLimit = _frameTimeLimit; }
    void SetLoop(bool _isLoop) { m_isLoop = _isLoop; }
};
