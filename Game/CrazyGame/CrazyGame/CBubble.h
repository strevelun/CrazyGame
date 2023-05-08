#pragma once
#include "CObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

class CMoveObj;

class CBubble :
    public CObj
{
    CAnimator           m_animator;
    CAnimationClip      m_animClip;

    //CPlayer* m_pPlayer = nullptr;
    CMoveObj* m_pOwner = nullptr;

    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 0;
    u_int m_attackPower = 25;

    bool m_bMoving = false;
    Dir m_eMovingDir = Dir::None;

    D2D1_POINT_2U m_prevCellPos;

public:
    CBubble(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CBubble();
    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void Move(Dir _eDir);

    void SetOwner(CMoveObj* _pOwner) { m_pOwner = _pOwner; }
    void SetSplashLength(u_int _splashLength) { m_splashLength = _splashLength; }

    void Die() override;

};
