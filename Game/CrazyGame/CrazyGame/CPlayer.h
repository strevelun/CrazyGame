#pragma once
#include "CMoveObj.h"
#include "Setting.h"

class CScene;
class CAnimation;

enum class Dir
{
    Up,
    Down,
    Right,
    Left,
    None
};

class CPlayer :
    public CMoveObj
{
    float m_speed = 210.0f;
    Dir m_eMoveDir = Dir::Down;
    Dir m_eLastMoveDir = Dir::Down;
    CScene* m_pScene = nullptr;
    bool m_bFire = false;
    bool m_isMoving = false;

public:
    CPlayer();
    ~CPlayer();

    void Input();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);
    void Die() override;

    void SetScene(CScene* _pScene) { m_pScene = _pScene; }
};

