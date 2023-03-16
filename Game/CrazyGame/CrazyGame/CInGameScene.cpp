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

CInGameScene::CInGameScene()
{
	
}

CInGameScene::~CInGameScene()
{
}

void CInGameScene::Init()
{
	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"StageFrame.png");

	CLayer* layer = CreateLayer("InGameUI", 0);

	CUIPanel* stageFrame = new CUIPanel();
	stageFrame->SetBitmap(bitmap);
	stageFrame->SetRect({ 0, 0, 1420.f, 1080 });
	layer->AddObj(stageFrame);

	CUIButton* backButton = new CUIButton("BackButton");
	backButton->SetRect({ 1150, 1010, 1400, 1080 });
	backButton->SetCallback(this, &CInGameScene::OnBackButtonClicked);
	layer->AddObj(backButton);

	m_board.resize(m_mapData.gridY);
	for (int i = 0; i < m_mapData.gridY; i++)
		m_board[i].resize(m_mapData.gridX);

	layer = CreateLayer("Tile", 1);


	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);

	u_int size = m_mapData.vecBlockData.size();
	for (int i = 0; i < size; i++)
	{
		if (m_mapData.vecBlockData[i].type != eType::Tile)
			continue;

		CTile* tile = new CTile();
		tile->SetRect(D2D1::RectF(
			m_mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + stageFrameOffsetX,
			m_mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + stageFrameOffsetY,
			m_mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE  + stageFrameOffsetX,
			m_mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE  + stageFrameOffsetY
			));
		tile->SetBitmapIdx(m_mapData.vecBlockData[i].idx);
		tile->SetSprite(CResourceManager::GetInst()->GetImage("Tile", m_mapData.vecBlockData[i].idx));
		layer->AddObj(tile);
	}

	layer = CreateLayer("Block",3);
	for (int i = 0; i < size; i++)
	{
		if (m_mapData.vecBlockData[i].type != eType::Block)
			continue;

		tSprite* sprite = CResourceManager::GetInst()->GetImage("Block", m_mapData.vecBlockData[i].idx);
		m_board[m_mapData.vecBlockData[i].y][m_mapData.vecBlockData[i].x] = eInGameObjType::Block;

		float right = m_mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX - (sprite->size.width < 30 ? BOARD_BLOCK_SIZE / 2 + 5 : 0);

		CTile* tile = new CTile();
		tile->SetRect(D2D1::RectF(
			m_mapData.vecBlockData[i].x * (float)BOARD_BLOCK_SIZE + stageFrameOffsetX,
			m_mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE - (sprite->size.height * ((float)BOARD_BLOCK_SIZE / 40)) + 137 - (sprite->size.width < 30 ? 7 : 0),
			right,
			m_mapData.vecBlockData[i].y * (float)BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE  - (sprite->size.width < 30 ? 7 : 0) + stageFrameOffsetY
		));
		tile->SetBitmapIdx(m_mapData.vecBlockData[i].idx);
		tile->SetSprite(sprite);
		layer->AddObj(tile);
	}

	float x, y;
	size = m_mapData.vecEventData.size();
	layer = CreateLayer("Character", 2);
	for (int i = 0; i < size; i++)
	{
		if (m_mapData.vecEventData[i] == eMenuEvent::Spawn_Character)
		{
			tSprite* sprite = CResourceManager::GetInst()->GetImage("Character", 0);
			y = i / m_mapData.gridY;
			x = i % m_mapData.gridY;
			m_board[y][x] = eInGameObjType::Character;
			CPlayer* player = new CPlayer();
			player->SetRect({
				sprite->rect.left + (x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				sprite->rect.top + (y * BOARD_BLOCK_SIZE) + stageFrameOffsetY,
				sprite->rect.right + (x * BOARD_BLOCK_SIZE)   + stageFrameOffsetX ,
				sprite->rect.bottom + (y * BOARD_BLOCK_SIZE)   + stageFrameOffsetY });
			CBitmap* bitmap = CResourceManager::GetInst()->GetIdxBitmap(sprite->idx);
			player->SetBitmap(bitmap);
			player->SetSprite(sprite);
			player->SetScene(this);
			layer->AddObj(player);
		}
		else if (m_mapData.vecEventData[i] == eMenuEvent::Spawn_Monster)
		{
			tSprite* sprite = CResourceManager::GetInst()->GetImage("Character", 1);
			y = i / m_mapData.gridY;
			x = i % m_mapData.gridY;
			m_board[y][x] = eInGameObjType::Boss;
			CMonster* monster = new CMonster();
			monster->SetRect({
				(x * BOARD_BLOCK_SIZE) + stageFrameOffsetX,
				(y * BOARD_BLOCK_SIZE)  + stageFrameOffsetY - sprite->size.height * 1.0f + BOARD_BLOCK_SIZE,
				(x * BOARD_BLOCK_SIZE) + sprite->size.width + stageFrameOffsetX ,
				(y * BOARD_BLOCK_SIZE) + sprite->size.height + stageFrameOffsetY - sprite->size.height * 1.0f + BOARD_BLOCK_SIZE });
			CBitmap* bitmap = CResourceManager::GetInst()->GetIdxBitmap(sprite->idx);
			monster->SetBitmap(bitmap);
			monster->SetSprite(sprite);
			layer->AddObj(monster);
		}
	}

	layer = CreateLayer("Event", 4);
}

void CInGameScene::OnBackButtonClicked(const std::string _strName)
{
	CLobbyScene* scene = CSceneManager::GetInst()->CreateScene<CLobbyScene>();
	CSceneManager::GetInst()->SetNextScene(scene);
}

bool CInGameScene::IsMovable(int _x, int _y)
{
	if (_x < 0) return false;
	if (_y < 0 ) return false;

	_x /= BOARD_BLOCK_SIZE;
	_y /= BOARD_BLOCK_SIZE;

	if (m_mapData.gridX <= _x) return false;
	if (m_mapData.gridY <= _y) return false;

	return m_board[_y][_x] != eInGameObjType::Block;
}

void CInGameScene::PutBubble(D2D1_RECT_F _rect)
{
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = _rect.left - stageFrameOffsetX;
	int bottom = _rect.top - stageFrameOffsetY + BOARD_BLOCK_SIZE / 2;

	int x = left / BOARD_BLOCK_SIZE;
	int y = bottom / BOARD_BLOCK_SIZE;

	if (m_mapData.gridX <= x) return;
	if (m_mapData.gridY <= y) return;

	if (m_board[y][x] != eInGameObjType::Balloon)
	{
		CLayer* layer = FindLayer("Event");
		if (layer)
		{
			m_board[y][x] = eInGameObjType::Balloon;
			CBubble* bubble = new CBubble();
			bubble->SetAnimation(CResourceManager::GetInst()->GetAnimation("bubble"));
			bubble->SetRect({
				(float)x * BOARD_BLOCK_SIZE + stageFrameOffsetX, 
				(float)y * BOARD_BLOCK_SIZE + stageFrameOffsetY,
				(float)x * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX,
				(float)y * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY
				});
			layer->AddObj(bubble);
		}
	}
}
