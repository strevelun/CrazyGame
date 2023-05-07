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

CInGameScene::CInGameScene()
{
	m_board = new CBoard();
}

CInGameScene::~CInGameScene()
{
	delete m_board;
}

void CInGameScene::Init()
{

	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"StageFrame.png");

	CLayer* layer = CreateLayer("InGameUI", 0);

	//CUIPanel* stageFrame = new CUIPanel({ 0, 0, 1420.f, 1080 });
	CUIPanel* stageFrame = new CUIPanel({ 0, 0, 800.f, 600.f });
	stageFrame->SetBitmap(bitmap);
	layer->AddObj(stageFrame);

	CUIButton* backButton = new CUIButton({ 647, 561, 786, 592 }, "BackButton");
	backButton->SetCallback(this, &CInGameScene::OnBackButtonClicked);
	layer->AddObj(backButton);

	m_board->SetBoard();

	layer = CreateLayer("MonsterUI", 6);

	layer = CreateLayer("Tile", 1);

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
		tile->SetSprite(CResourceManager::GetInst()->GetImage("Tile", mapData.vecBlockData[i].idx));
		layer->AddObj(tile);
	}

	layer = CreateLayer("Block",3);
	for (int i = 0; i < size; i++)
	{
		if (mapData.vecBlockData[i].type != eType::Block)
			continue;

		tSprite* sprite = CResourceManager::GetInst()->GetImage("Block", mapData.vecBlockData[i].idx);
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
			layer = CreateLayer("Flag", INT_MAX);
			layer->AddObj(block);
			layer = FindLayer("Block");
		}
		else 
			layer->AddObj(block);
	}

	float x, y;
	size = mapData.vecEventData.size();

	int boardBlockSizeHalf = (BOARD_BLOCK_SIZE / 2);

	for (int i = 0; i < size; i++)
	{
		if (mapData.vecEventData[i] == eMenuEvent::Spawn_Character)
		{
			tSprite* sprite = CResourceManager::GetInst()->GetImage("Character", 0);
			y = i / mapData.gridX;
			x = i % mapData.gridX;
			
			m_pPlayer = new CPlayer({
				(x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				(y * BOARD_BLOCK_SIZE) + stageFrameOffsetY - (sprite->size.height - BOARD_BLOCK_SIZE),
				boardBlockSizeHalf + (x * BOARD_BLOCK_SIZE) + stageFrameOffsetX + (sprite->size.width / 2),
				BOARD_BLOCK_SIZE + (y * BOARD_BLOCK_SIZE) + stageFrameOffsetY }
			, eInGameObjType::Character);
			m_board->SetObjTypeInMoveObjBoard(x, y, m_pPlayer);
 
			m_pPlayer->SetSprite(sprite);
			m_pPlayer->SetScene(this);
			layer->AddObj(m_pPlayer);
		}
		else if (mapData.vecEventData[i] == eMenuEvent::Spawn_Monster) // º¸½º
		{
			tSprite* sprite = CResourceManager::GetInst()->GetImage("Character", 1);
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
			m_board->SetObjTypeInMoveObjBoard(x, y, boss);
			boss->SetSprite(sprite);
			layer->AddObj(boss);
		}
		else if (mapData.vecEventData[i] == eMenuEvent::Blocked)
		{
			y = i / mapData.gridY;
			x = i % mapData.gridY;
			m_board->SetInGameObjType(mapData.vecBlockData[i].x, mapData.vecBlockData[i].y, eInGameObjType::Block_InDestructible);
		}
	}

	layer = CreateLayer("Event", 4);
	layer = CreateLayer("Vehicle", 5);
}

void CInGameScene::OnBackButtonClicked(const std::string _strName)
{
	CLobbyScene* scene = dynamic_cast<CLobbyScene*>(CSceneManager::GetInst()->GetScene("LobbyScene"));
	CSceneManager::GetInst()->ChangeScene("LobbyScene");
	
}