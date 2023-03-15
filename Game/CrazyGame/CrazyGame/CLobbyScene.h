#pragma once

#include "CScene.h"
#include "Setting.h"
#include <unordered_map>

class CScene;

// 로비씬에서 할당한 자원은 계속 유지

class CLobbyScene :
    public CScene
{
    std::unordered_map<std::string, tMapData> m_mapData; // 한번에 다 로딩해서 가지고 있지 말기

public:
    CLobbyScene();
    ~CLobbyScene();

    void OnMapButtonClicked(const std::string _strName);
    tMapData& FindMapData(const std::string& _strName);
};

