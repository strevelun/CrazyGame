#pragma once
#include "CMoveObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

class CMoveObj;

class CBubble :
    public CMoveObj
{
    CMoveObj* m_pOwner = nullptr;

    double m_angle = 45.0;
    double m_gravity = 0.5;
    int m_throwLimit = 10;
    int m_curThrow = 0;

    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 0;
    u_int m_attackPower = 25;

    bool m_bMoving = false;
    bool m_bBounceMoving = false;
    eDir m_eMovingDir = eDir::None;

    D2D1_POINT_2U m_prevCellPos;

public:
    CBubble(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CBubble();
    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void Move(eDir _eDir);
    void BounceMove(eDir _eDir);

    void SetOwner(CMoveObj* _pOwner) { m_pOwner = _pOwner; }
    void SetSplashLength(u_int _splashLength) { m_splashLength = _splashLength; }

    void Die() override;

};
