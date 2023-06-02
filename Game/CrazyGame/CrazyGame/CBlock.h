#pragma once
#include "CStaticObj.h"

class CItem;

enum class eBlockState
{
    None,
    Idle,
    Moving
};

class CBlock :
    public CStaticObj
{
    CItem* m_pItem = nullptr;
    float m_moveTime = 0.0f; // 플레이어가 벽에 대고 얼마나 누르고 있으면 움직이는지
    float m_moveTimeLimit = 0.5f;
    eBlockState m_eBlockState;

    int m_dirX = 0, m_dirY = 0;

public:
    CBlock(const D2D1_RECT_F& _rect);
    ~CBlock();

    void Update() override;
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

    void Move(eDir _eDir);
    void Die() override;
};

