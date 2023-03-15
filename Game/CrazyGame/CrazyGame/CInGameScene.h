#pragma once
#include "CScene.h"
#include "Setting.h"
#include <vector>

class CInGameScene :
    public CScene
{
    tMapData m_mapData;
    std::vector<std::vector<eInGameObjType>> m_board;

public:
    CInGameScene();
    ~CInGameScene();

    void Init();

    void SetMapData(tMapData _mapData) { m_mapData = _mapData; }
    void OnBackButtonClicked(const std::string _strName);
};

