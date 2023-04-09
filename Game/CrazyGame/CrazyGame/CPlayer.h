#pragma once
#include "CMoveObj.h"
#include "Setting.h"

class CScene;
class CAnimator;
class CAnimationClip;
class CVehicle;

enum class Player_State
{
    Ready,
    Idle,
    Move,
    Die,
};

class CPlayer :
    public CMoveObj
{
    float m_speed = 210.0f;
    float m_prevSpeed = 210.0f;
    float m_jumpRate = 1.0f;
   // D2D1_RECT_F m_jumpRect;
    D2D1_RECT_F m_rideRect;
    Dir m_eMoveDir = Dir::Down;
    Dir m_eLastMoveDir = Dir::Down;
    Player_State m_state = Player_State::Ready;
    Player_State m_prevState = Player_State::Ready;
    CAnimationClip* m_animDir[4];

    bool m_bFire = false;
    bool m_bKickable = true;
    bool m_bIsJumping = false;
    bool m_bIsRiding = false;

    u_int m_bubbleCarryLimit = 1;
    u_int m_curBubblePlaced = 0;
    u_int m_splashLength = 3;

    CVehicle* m_vehicle = nullptr;

private:

public:
    CPlayer(const D2D1_RECT_F& _rect);
    ~CPlayer();

    void Input();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);
    void Die() override;

    // state func
    void MoveState();

    std::string GetStrDir(Dir _dir);
    void ReduceCurBubble(u_int _numOfBubbles) { m_curBubblePlaced -= _numOfBubbles; }
};

