#pragma once
#include "CScene.h"
#include "Setting.h"
#include "CBoard.h"

class CPlayer;

class CInGameScene :
    public CScene
{
private:
    friend class CBlock;
    friend class CPlayer;
    friend class CMoveObj;
    friend class CBubble;
    friend class CLayer;

    CPlayer*    m_pPlayer;
    CBoard*     m_board;

public:
    CInGameScene();
    ~CInGameScene();

    void Init() override;
    void Cleanup() override;

    CPlayer* GetPlayer() const { return m_pPlayer; }
    void SetMapData(tMapData _mapData) { m_board->SetMapData(_mapData); }
    void OnBackButtonClicked(const std::string _strName);
    CBoard* GetBoard() const { return m_board; }
};

