#pragma once
#include "CMoveObj.h"
class CMonster :
    public CMoveObj
{
private:
    float m_passiveTime = 0.0f;
    float m_passiveTimeLimit = 1.0f;

public:
    CMonster(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CMonster();

    void MoveState();
    void ChangeState(State _state);
    State RandomDir();

    void Die() override;
    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
};

