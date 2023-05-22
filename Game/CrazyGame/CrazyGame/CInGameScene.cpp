#include "CInGameScene.h"
#include "CUIPanel.h"
#include "CResourceManager.h"
#include "CTile.h"
#include "Setting.h"
#include "CUIButton.h"
#include "CSceneManager.h"
#include "CLobbyScene.h"
#include "CPlayer.h"
#include "../../D2DCore/CApp.h"
#include "CBoss.h"
#include "CBubble.h"
#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CBlock.h"
#include "CTimer.h"
#include "CBitmap.h"
#include "Stage.h"
#include "StageManager.h"
#include "UIManager.h"


CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

void CInGameScene::Init()
{

	m_stage = new Stage();
	StageManager::GetInst()->ChangeStage(m_stage);

	m_board = new CBoard();
	m_board->SetMapData(CResourceManager::GetInst()->LoadMapData(m_strName.c_str()));

	//CMapInfo::GetInstance()->GetSelectMap();
	//m_board->SetMapData(L"village.map");

	CBitmap* bitmap = CResourceManager::GetInst()->GetBitmap(L"StageFrame.png");

	CLayer* layer = CreateLayer(L"InGameUI", 0);

	CUIPanel* stageFrame = new CUIPanel({ 0, 0, 800.f, 600.f });
	stageFrame->SetBitmap(bitmap);
	layer->AddObj(stageFrame);

	CUIButton* backButton = new CUIButton({ 647, 561, 786, 592 }, L"BackButton");
	backButton->SetCallback(this, &CInGameScene::OnBackButtonClicked);
	layer->AddObj(backButton);

	m_board->SetBoard();

	layer = CreateLayer(L"MonsterUI", 6);

	layer = CreateLayer(L"Tile", 1);

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	tMapData mapData = m_board->GetMapData();
	u_int size = mapData.vecBlockData.size();
	for (int i = 0; i < size; i++)
	{
		if (mapData.vecBlockData[i].type != eType::Tile)
			continue;

		CTile* tile = new CTile(D2D1::RectF(
			mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + stageFrameOffsetX,
			mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + stageFrameOffsetY,
			mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX,
			mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY
		));
		tile->SetBitmapIdx(mapData.vecBlockData[i].idx);
		tile->SetSprite(CResourceManager::GetInst()->GetSprite(L"Tile", mapData.vecBlockData[i].idx));
		layer->AddObj(tile);
	}

	layer = CreateLayer(L"Block",3);
	for (int i = 0; i < size; i++)
	{
		if (mapData.vecBlockData[i].type != eType::Block)
			continue;

		tSprite* sprite = CResourceManager::GetInst()->GetSprite(L"Block", mapData.vecBlockData[i].idx);
		m_board->SetInGameObjType(mapData.vecBlockData[i].x, mapData.vecBlockData[i].y, eInGameObjType::Block_Destructible);

		float right = mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX - (sprite->size.width < 30 ? BOARD_BLOCK_SIZE / 2 + 5 : 0);

		CBlock* block = new CBlock(D2D1::RectF(
			mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + stageFrameOffsetX,
			mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE - (sprite->size.height - BOARD_BLOCK_SIZE) - (sprite->size.width < 30 ? 3 : 0) + stageFrameOffsetY,
			right,
			mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE - (sprite->size.width < 30 ? 2 : 0) + stageFrameOffsetY
		));

		block->SetBitmapIdx(mapData.vecBlockData[i].idx);
		block->SetSprite(sprite);
		if (sprite->size.width < 30)
		{
			layer = CreateLayer(L"Flag", INT_MAX);
			layer->AddObj(block);
			layer = FindLayer(L"Block");
		}
		else 
			layer->AddObj(block);
	}

	float x, y;
	size = mapData.vecEventData.size();

	int boardBlockSizeHalf = (BOARD_BLOCK_SIZE / 2);
	//bool isBossHere = false;

	for (int i = 0; i < size; i++)
	{
		if (mapData.vecEventData[i] == eMenuEvent::Spawn_Character)
		{
			tSprite* sprite = CResourceManager::GetInst()->GetSprite(L"Character", 0);
			y = i / mapData.gridX;
			x = i % mapData.gridX;
			
			m_pPlayer = new CPlayer({
				(x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				(y * BOARD_BLOCK_SIZE) + stageFrameOffsetY - (sprite->size.height - BOARD_BLOCK_SIZE),
				boardBlockSizeHalf + (x * BOARD_BLOCK_SIZE) + stageFrameOffsetX + (sprite->size.width / 2),
				BOARD_BLOCK_SIZE + (y * BOARD_BLOCK_SIZE) + stageFrameOffsetY }
			, eInGameObjType::Character);
			m_board->SetObjTypeInMoveObjBoard(x, y, m_pPlayer);
 
			//m_pPlayer->SetSprite(sprite);
			m_pPlayer->SetScene(this);
			layer->AddObj(m_pPlayer);
		}
		else if (mapData.vecEventData[i] == eMenuEvent::Spawn_Monster) // 보스
		{
			tSprite* sprite = CResourceManager::GetInst()->GetSprite(L"Character", 1);
			y = i / mapData.gridX;
			x = i % mapData.gridX;
			CBoss* boss = new CBoss({
				(x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				(y * BOARD_BLOCK_SIZE) + stageFrameOffsetY - 170 + BOARD_BLOCK_SIZE,
				(x * BOARD_BLOCK_SIZE) + 120 + stageFrameOffsetX ,
				(y * BOARD_BLOCK_SIZE)  + stageFrameOffsetY + BOARD_BLOCK_SIZE }
			, eInGameObjType::Boss);

			boss->SetScene(this);

			if (boss->Init() == false)
			{
				delete boss;
				continue;
			}
			//isBossHere = true;
			m_board->SetObjTypeInMoveObjBoard(x, y, boss);
			//boss->SetSprite(sprite);
			layer->AddObj(boss);
		}
		else if (mapData.vecEventData[i] == eMenuEvent::Blocked)
		{
			y = i / mapData.gridY;
			x = i % mapData.gridY;
			m_board->SetInGameObjType(mapData.vecBlockData[i].x, mapData.vecBlockData[i].y, eInGameObjType::Block_InDestructible);
		}
	}

	m_stage->AddMoveObjCnt(MoveObjType::Boss); // 보스가 없으면 플레이어가 죽을때까지 게임 안끝남


	layer = CreateLayer(L"Event", 4);
	layer = CreateLayer(L"Vehicle", 5);

	layer = FindLayer(L"MonsterUI");
	UIManager::GetInst()->ShowAndAddUIPanel(L"start.png");

}

void CInGameScene::Cleanup()
{
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->DeleteAllObj();
		delete* iter;
	}
	m_layerList.clear();

	delete m_board;
	m_stage->Cleanup();
}

void CInGameScene::Update()
{
	CScene::Update();

	m_stage ->Update();
}


void CInGameScene::OnBackButtonClicked(const std::wstring _strName)
{
	//CLobbyScene* scene = dynamic_cast<CLobbyScene*>(CSceneManager::GetInst()->GetScene(L"LobbyScene"));
	CSceneManager::GetInst()->ChangeScene(L"LobbyScene");
	
}


