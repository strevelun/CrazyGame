#pragma once
#include "CMoveObj.h"
#include "Setting.h"

class CScene;
class CAnimator;
class CAnimationClip;



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
    Dir m_eMoveDir = Dir::Down;
    Dir m_eLastMoveDir = Dir::Down;
    Player_State m_state = Player_State::Ready;
    Player_State m_prevState = Player_State::Ready;
    CAnimationClip* m_animDir[4];

    bool m_bFire = false;
    bool m_bKickable = true;
    u_int m_bubbleCarryLimit = 1;
    u_int m_curBubblePlaced = 0;

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

