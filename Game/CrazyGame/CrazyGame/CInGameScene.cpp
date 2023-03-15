#include "CInGameScene.h"
#include "CUIPanel.h"
#include "CResourceManager.h"
#include "CTile.h"
#include "Setting.h"
#include "CUIButton.h"
#include "CSceneManager.h"
#include "CLobbyScene.h"

CInGameScene::CInGameScene()
{
	
}

CInGameScene::~CInGameScene()
{
}

void CInGameScene::Init()
{
	CBitmap* bitmap = CResourceManager::GetInst()->Load(L"StageFrame.png");

	CLayer* layer = CreateLayer("InGameUI", INT_MAX);

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

	layer = CreateLayer("Tile", 0);

	u_int size = m_mapData.vecBlockData.size();
	for (int i = 0; i < size; i++)
	{
		if (m_mapData.vecBlockData[i].type != eType::Tile)
			continue;

		CTile* tile = new CTile();
		tile->SetRect(D2D1::RectF(
			m_mapData.vecBlockData[i].x * BOARD_BLOCK_SIZE + 40,
			m_mapData.vecBlockData[i].y * BOARD_BLOCK_SIZE + 80,
			m_mapData.vecBlockData[i].x * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40,
			m_mapData.vecBlockData[i].y * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 80
			));
		tile->SetBitmapIdx(m_mapData.vecBlockData[i].idx);
		tile->SetSprite(CResourceManager::GetInst()->GetImage("Tile", m_mapData.vecBlockData[i].idx));
		layer->AddObj(tile);
	}

	layer = CreateLayer("Block", 1);
	for (int i = 0; i < size; i++)
	{
		if (m_mapData.vecBlockData[i].type != eType::Block)
			continue;

		tSprite* sprite = CResourceManager::GetInst()->GetImage("Block", m_mapData.vecBlockData[i].idx);
		m_board[m_mapData.vecBlockData[i].y][m_mapData.vecBlockData[i].x] = eInGameObjType::Block;

		float right = m_mapData.vecBlockData[i].x * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40 - (sprite->size.width < 30 ? BOARD_BLOCK_SIZE / 2 + 5 : 0);

		CTile* tile = new CTile();
		tile->SetRect(D2D1::RectF(
			m_mapData.vecBlockData[i].x * BOARD_BLOCK_SIZE + 40,
			m_mapData.vecBlockData[i].y * BOARD_BLOCK_SIZE - (sprite->size.height * (BOARD_BLOCK_SIZE / 40)) + 115 + (sprite->size.width < 30 ? 90 : 0),
			right,
			m_mapData.vecBlockData[i].y * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 80 + (sprite->size.width < 30 ? 60 : 0)
		));
		tile->SetBitmapIdx(m_mapData.vecBlockData[i].idx);
		tile->SetSprite(sprite);
		layer->AddObj(tile);
	}

	layer = CreateLayer("Character", 2);

	layer = CreateLayer("Event", 3);

}

void CInGameScene::OnBackButtonClicked(const std::string _strName)
{
	CLobbyScene* scene = CSceneManager::GetInst()->CreateScene<CLobbyScene>();
	CSceneManager::GetInst()->SetNextScene(scene);
}
