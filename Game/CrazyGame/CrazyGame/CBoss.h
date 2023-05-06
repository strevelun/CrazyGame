#pragma once
#include "CMoveObj.h"

#include "CAStar.h"

class CBoss :
    public CMoveObj
{
    //CAStar m_aStar;
    u_int m_hp = 50;

public:
    CBoss(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CBoss();

    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void Hit(u_int _attackPower);
    bool IsMovable(int _cellXPos, int _cellYPos);
    bool SetBossInMoveObjBoard(int _cellXPos, int _cellYPos, CMoveObj* _obj);
    void MoveState();
    void ChangeState(State _state) override;
    State GetState() const { return m_state; }
    void Die() override;

    State RandomDir();
};

