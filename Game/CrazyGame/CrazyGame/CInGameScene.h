#pragma once
#include "CScene.h"
#include "Setting.h"

class CInGameScene :
    public CScene
{
    tMapData m_mapData;

public:
    CInGameScene();
    ~CInGameScene();

    void Init();

    void SetMapData(tMapData _mapData) { m_mapData = _mapData; }
};

