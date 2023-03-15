#pragma once

#include "CScene.h"
#include "Setting.h"
#include <unordered_map>

class CScene;

// �κ������ �Ҵ��� �ڿ��� ��� ����

class CLobbyScene :
    public CScene
{
    std::unordered_map<std::string, tMapData> m_mapData; // �ѹ��� �� �ε��ؼ� ������ ���� ����

public:
    CLobbyScene();
    ~CLobbyScene();

    void OnMapButtonClicked(const std::string _strName);
    tMapData& FindMapData(const std::string& _strName);
};

