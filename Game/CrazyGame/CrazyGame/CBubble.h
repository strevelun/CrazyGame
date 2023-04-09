#pragma once
#include "CObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

class CPlayer;

class CBubble :
    public CObj
{
    CAnimator           m_animator;
    CAnimationClip      m_animClip;

    CPlayer* m_pPlayer = nullptr;;

    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 3;

    bool m_bMoving = false;
    Dir m_eMovingDir = Dir::None;

    D2D1_POINT_2U m_prevCellPos;

public:
    CBubble(const D2D1_RECT_F& _rect);
    ~CBubble();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);
    void Move(Dir _eDir);

    void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }

    void Die() override;

};
