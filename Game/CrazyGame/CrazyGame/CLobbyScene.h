#pragma once

#include "CScene.h"
#include "Setting.h"
#include <unordered_map>

class CScene;

// �κ������ �Ҵ��� �ڿ��� ��� ����

class CLobbyScene :
    public CScene
{

public:
    CLobbyScene();
    ~CLobbyScene();

    void OnMapButtonClicked(const std::string _strName);

    void Init() override;
};

