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

    void OnMapButtonClicked(const std::wstring _strName);

    void Init() override;
    void Cleanup() override;
};

