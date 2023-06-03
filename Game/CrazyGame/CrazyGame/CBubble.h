#pragma once
#include "CMoveObj.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

class Skill;

class CMoveObj;


class CBubble :
    public CMoveObj
{
    friend class BounceMoveSkill;
    friend class KickSkill;

    CMoveObj* m_pOwner = nullptr; // ex. 보스가 만든 물풍선이 터지면 그 스플래시에 몬스터는 데미지를 입지 않음

    Skill* m_pSkill = nullptr;

    float m_elapsedTime;
    float m_dieTime = 3.0f;
    u_int m_splashLength = 0;
    u_int m_attackPower = 25;

    float m_moveTime = 0.0f, m_moveTimeLimit = 0.2f;

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
