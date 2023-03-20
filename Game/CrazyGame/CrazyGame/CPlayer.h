#pragma once
#include "CObj.h"
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
    public CObj
{
    float m_speed = 210.0f;
    Dir m_eMoveDir = Dir::None;
    CScene* m_pScene = nullptr;

public:
    CPlayer();
    ~CPlayer();

    void Input();
    void Update();
    void Render(ID2D1RenderTarget* _pRenderTarget);

    void SetScene(CScene* _pScene) { m_pScene = _pScene; }
};

