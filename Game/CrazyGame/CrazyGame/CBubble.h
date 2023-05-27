#pragma once
#include "CMoveObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

class CMoveObj;

enum class eThrowState
{
    None,
    InAir,
    Bounce
};

class CBubble :
    public CMoveObj
{
    CMoveObj* m_pOwner = nullptr;

    float m_angle = 45.0f;
    float m_gravity = 9.8f;
    float m_ballTime = 0.0f;

    int m_throwLimit = 10;
    int m_curThrow = 0;

    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 0;
    u_int m_attackPower = 25;



    bool m_bMoving = false;
    bool m_bBounceMoving = false;
    eDir m_eMovingDir = eDir::None;
    eThrowState m_eThrowState = eThrowState::None; // 좌우로 던질떄만

    int m_dirX = 0, m_dirY = 0;

    D2D1_POINT_2U m_prevCellPos;

private:
    void BounceMoveSkill();
    void KickSkill();
    void SetDir(eDir _eDir);

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
