#pragma once
#include "CScene.h"
#include "Setting.h"
#include "CBoard.h"

#include <unordered_map>

class CPlayer;
class CUIPanel;
class Stage;


class CInGameScene :
    public CScene
{
private:
    friend class CBlock;
    friend class CPlayer;
    friend class CMoveObj;
    friend class CBubble;
    friend class CLayer;

    Stage*  m_stage;

    CPlayer*    m_pPlayer;
    CBoard*     m_board;

    std::unordered_map<std::wstring, tMapData> m_mapData;

public:
    CInGameScene();
    ~CInGameScene();

    void Init() override;
    void Cleanup() override;

    void Update() override;

    CPlayer* GetPlayer() const { return m_pPlayer; }
    CBoard* GetBoard() const { return m_board; }

    void OnBackButtonClicked(const std::wstring _strName);

};

