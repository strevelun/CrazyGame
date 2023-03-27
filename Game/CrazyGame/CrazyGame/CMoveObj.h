#pragma once
#include "CObj.h"
class CMoveObj :
    public CObj
{
protected:
    CScene* m_pScene = nullptr;

public:
    CMoveObj();
    ~CMoveObj();


protected:
    void MoveOnMoveObjBoard();

public:
    void SetScene(CScene* _pScene) { m_pScene = _pScene; }
};

