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
#include "CMonster.h"
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

	CUIPanel* stageFrame = new CUIPanel({ 0, 0, 1420.f, 1080 });
	//CUIPanel* stageFrame = new CUIPanel({ 0, 0, 800.f, 600.f });
	stageFrame->SetBitmap(bitmap);
	layer->AddObj(stageFrame);

	CUIButton* backButton = new CUIButton({ 1150, 1010, 1400, 1080 }, "BackButton");
	backButton->SetCallback(this, &CInGameScene::OnBackButtonClicked);
	layer->AddObj(backButton);

	m_board->SetBoard();

	layer = CreateLayer("Tile", 1);

	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);

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
			mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE - (sprite->size.height * ((float)BOARD_BLOCK_SIZE / 40)) + 137 - (sprite->size.width < 30 ? 7 : 0),
			right,
			mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE - (sprite->size.width < 30 ? 7 : 0) + stageFrameOffsetY
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
	for (int i = 0; i < size; i++)
	{
		if (mapData.vecEventData[i] == eMenuEvent::Spawn_Character)
		{
			tSprite* sprite = CResourceManager::GetInst()->GetImage("Character", 0);
			y = i / mapData.gridX;
			x = i % mapData.gridX;
			m_board->SetObjTypeInMoveObjBoard(x, y, eInGameObjType::Character);
			m_pPlayer = new CPlayer({
				sprite->rect.left + (x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				sprite->rect.top + (y * BOARD_BLOCK_SIZE) + stageFrameOffsetY - 20,
				BOARD_BLOCK_SIZE  + (x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				sprite->rect.bottom + (y * BOARD_BLOCK_SIZE) + stageFrameOffsetY });
 
			m_pPlayer->SetSprite(sprite);
			m_pPlayer->SetScene(this);
			layer->AddObj(m_pPlayer);
		}
		else if (mapData.vecEventData[i] == eMenuEvent::Spawn_Monster)
		{
			tSprite* sprite = CResourceManager::GetInst()->GetImage("Character", 1);
			y = i / mapData.gridX;
			x = i % mapData.gridX;
			m_board->SetObjTypeInMoveObjBoard(x, y, eInGameObjType::Boss);
			CMonster* monster = new CMonster({
				(x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				(y * BOARD_BLOCK_SIZE) + stageFrameOffsetY - sprite->size.height * 1.0f + BOARD_BLOCK_SIZE,
				(x * BOARD_BLOCK_SIZE) + sprite->size.width + stageFrameOffsetX ,
				(y * BOARD_BLOCK_SIZE) + sprite->size.height + stageFrameOffsetY - sprite->size.height * 1.0f + BOARD_BLOCK_SIZE });
			CBitmap* bitmap = CResourceManager::GetInst()->GetIdxBitmap(sprite->idx);
			monster->SetBitmap(bitmap);
			monster->SetSprite(sprite);
			monster->SetScene(this);
			layer->AddObj(monster);
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