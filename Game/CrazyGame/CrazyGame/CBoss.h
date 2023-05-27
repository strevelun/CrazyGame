#pragma once
#include "CMoveObj.h"

#include "CAStar.h"

class StageManager;

class CBoss :
    public CMoveObj
{
    u_int m_hp = 125;
    class CUIHPBar* m_uiHPBar;

    float m_attackDelay = 5.0f;
    float m_attackDelayRemained = 0.0f;

    StageManager* m_smInst;

public:
    CBoss(const D2D1_RECT_F& _rect, eInGameObjType _type);
    ~CBoss();
    bool Init();

    void Update();
    void Render(ID2D1BitmapRenderTarget* _pRenderTarget);
    void Hit(u_int _attackPower);
    bool IsMovable(int _cellXPos, int _cellYPos);
    bool SetBossInMoveObjBoard(int _cellXPos, int _cellYPos, CMoveObj* _obj);
    void MoveState();
    void ChangeState(State _state) override;
    State GetState() const { return m_state; }
    void Die() override;

    void Attack();

    State RandomDir();

private:
    void Attack01(CBoard* _pBoard);
    void Attack02(CBoard* _pBoard);

    bool CanMoveTo(float _xpos, float _ypos, float _delta, eDir _eDir); // 기준점(x,y)가 deltaTime * speed를 적용받은 후 맵 밖을 나가는지 확인
};

