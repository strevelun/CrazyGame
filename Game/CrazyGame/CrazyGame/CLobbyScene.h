#pragma once

#include "CScene.h"
#include "Setting.h"
#include <unordered_map>

class CScene;

// �κ������ �Ҵ��� �ڿ��� ��� ����

class CLobbyScene :
    public CScene
{
    std::unordered_map<std::string, tMapData> m_mapData;

public:
    CLobbyScene();
    ~CLobbyScene();

    void OnMapButtonClicked(std::string _strName);
};

