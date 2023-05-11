#pragma once
#include "CScene.h"
#include "Setting.h"
#include "CBoard.h"

class CPlayer;
class CUIPanel;

enum class eSceneState
{
    Ready,
    Play,
    End
};

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
    eSceneState  m_eSceneState;

    CUIPanel* m_statePanel;

    float m_fPlayTime;
    u_int m_bossCount = 0;
    u_int m_monsterCount = 0;
    u_int m_playerCount = 1;

public:
    CInGameScene();
    ~CInGameScene();

    void Init() override;
    void Cleanup() override;

    void Update() override;

    void AddMonsterCount() { m_monsterCount++; }
    void SubMonsterCount() { m_monsterCount--; }
    void AddBossCount() { m_bossCount++; }
    void SubBossCount() { m_bossCount--; }
    void SubPlayerCount() { m_playerCount--; }

    void SetSceneState(eSceneState _state) { m_eSceneState = _state; }


    CPlayer* GetPlayer() const { return m_pPlayer; }
    CBoard* GetBoard() const { return m_board; }
    eSceneState GetSceneState() const { return m_eSceneState; }

    void OnBackButtonClicked(const std::string _strName);

private:
    void CheckState();
    void ShowStatePanel(PCWSTR _strFileName);
};

