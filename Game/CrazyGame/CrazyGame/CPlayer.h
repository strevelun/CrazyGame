#pragma once
#include "CMoveObj.h"
#include "Setting.h"

class CScene;
class CAnimator;
class CAnimationClip;
class CVehicle;

class StageManager;

class CPlayer :
    public CMoveObj
{
 
    float m_prevSpeed = 210.0f; // ž�� �� �ӵ�
    //float m_jumpRate = 1.0f;
    D2D1_RECT_F m_rideRect;
    //CAnimationClip* m_animDir[4];

    int m_spaceCount = 0;
    bool m_spacePressed = false;
    float m_doubleSpaceDeltaTime = 0.0f;
    float m_attackDelay = 0.2f;

    bool m_bFire = false;
    bool m_bKickable = true;
    bool m_bIsRiding = false;
    bool m_bInvincible = false;

    u_int m_bubbleCarryLimit = 5;
    u_int m_curBubblePlaced = 0;
    u_int m_splashLength = 1;
    float m_invincibleTime = 0.0f;
    bool m_bIsJumping = false;
    bool m_bIsGettingOff = false;

    CVehicle* m_vehicle = nullptr;
    StageManager* m_smInst;

    ID2D1Bitmap* m_pShadow = nullptr;

private:

public:
    CPlayer(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CPlayer();

    void Input();
    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void Die() override;

    //CVehicle* GetVehicle() const { return m_vehicle; }

    // state func
    void MoveState();
    void ReadyState();

    void ChangeState(State _state) override;

    std::wstring GetStrDir(eDir _dir);
    //void ReduceCurBubble(u_int _numOfBubbles) { m_curBubblePlaced -= _numOfBubbles; }
    void GetOffVehicle();


    CVehicle*   GetVehicle() const { return m_vehicle; }
    void        ReduceCurBubble(u_int _numOfBubbles) { m_curBubblePlaced -= _numOfBubbles; }
};

