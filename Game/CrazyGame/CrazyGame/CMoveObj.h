#pragma once
#include "CObj.h"
class CMoveObj :
    public CObj
{
protected:
    CScene* m_pScene = nullptr;

public:
    CMoveObj(const D2D1_RECT_F& _rect);
    ~CMoveObj();


protected:
    void MoveOnMoveObjBoard(eInGameObjType _type);

public:
    void SetScene(CScene* _pScene) { m_pScene = _pScene; }
};

