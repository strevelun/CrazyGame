#pragma once
#include "CObj.h"

enum class State
{
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Ready,
    Idle,
    Attack,
    TrappedInBubble,
    Die,
    Hit,
    None,
};

class CMoveObj :
    public CObj
{
protected:
    CScene* m_pScene = nullptr;
    float m_speed = 0.0f;
   // Dir m_eMoveDir = Dir::Down;
    //Dir m_eLastMoveDir = Dir::Down;
    State m_state = State::Ready;
    State m_nextState = State::Ready;



public:
    CMoveObj(const D2D1_RECT_F& _rect);
    ~CMoveObj();


protected:
    void MoveOnMoveObjBoard(CMoveObj* _obj);
    virtual void ChangeState(State _state);

public:
    void SetScene(CScene* _pScene) { m_pScene = _pScene; }
};

