#pragma once
#include "CMoveObj.h"
#include "Setting.h"

class CScene;
class CAnimator;

enum class Dir
{
    Up,
    Down,
    Right,
    Left,
    None
};

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
    bool m_bFire = false;
    Player_State m_state = Player_State::Ready;

private:

public:
    CPlayer();
    ~CPlayer();

    void Input();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);
    void Die() override;

    std::string GetStrDir(Dir _dir);
};

