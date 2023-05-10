#pragma once
#include "CMoveObj.h"
class CMonster :
    public CMoveObj
{
public:
    CMonster(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CMonster();

    void MoveState();
    void ChangeState(State _state);
    State RandomDir();

    void Hit();
    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
};

