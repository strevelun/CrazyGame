#pragma once
#include "CScene.h"
#include "Setting.h"
#include "CBoard.h"

class CInGameScene :
    public CScene
{
    friend class CPlayer;
    friend class CLayer;


    CBoard* m_board;

public:
    CInGameScene();
    ~CInGameScene();

    void Init();

    void SetMapData(tMapData _mapData) { m_board->SetMapData(_mapData); }
    void OnBackButtonClicked(const std::string _strName);

};

