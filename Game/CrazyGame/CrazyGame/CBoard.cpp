#include "CBoard.h"
#include "CInGameScene.h"
#include "CSceneManager.h"
#include "CBubble.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CSplash.h"
#include "CPlayer.h"
#include "CObj.h"
#include "CItem.h"
#include "CVehicle.h"
 
CBoard::CBoard()
{
}

CBoard::~CBoard()
{
	// m_board.clear();
	m_moveObjBoard.clear();
}

void CBoard::SetBoard()
{
	m_board.resize(m_mapData.gridY);
	for (int i = 0; i < m_mapData.gridY; i++)
		m_board[i].resize(m_mapData.gridX);

	m_moveObjBoard.resize(m_mapData.gridY);
	for (int i = 0; i < m_mapData.gridY; i++)
		m_moveObjBoard[i].resize(m_mapData.gridX);

	m_itemBoard.resize(m_mapData.gridY);
	for (int i = 0; i < m_mapData.gridY; i++)
		m_itemBoard[i].resize(m_mapData.gridX);
}

bool CBoard::IsMovable(u_int _xpos, u_int _ypos, CVehicle* _vehicle)
{
	if (m_mapData.gridX <= _xpos) return false;
	if (m_mapData.gridY <= _ypos) return false;

	if (_vehicle && _vehicle->GetName().compare("UFO") == 0
		&& m_board[_ypos][_xpos] != eInGameObjType::Block_InDestructible)
	{
		return true;
	}

	if (m_board[_ypos][_xpos] == eInGameObjType::Block_Destructible || m_board[_ypos][_xpos] == eInGameObjType::Block_InDestructible
		|| m_board[_ypos][_xpos] == eInGameObjType::Balloon)
		return false;

	return true;
}

bool CBoard::IsGameObjType(int x, int y, eInGameObjType _type)
{

	if (m_mapData.gridX <= x) return false;
	if (m_mapData.gridY <= y) return false;

	if (_type == eInGameObjType::Character || _type == eInGameObjType::Monster
		|| _type == eInGameObjType::Boss)
		return m_moveObjBoard[y][x] == _type;
	else
		return m_board[y][x] == _type;
}

// 사실상 물풍선 전용
bool CBoard::PutObj(int _xpos, int _ypos, CObj* _obj, eInGameObjType _type)
{
	if (m_mapData.gridX <= _xpos) return false;
	if (m_mapData.gridY <= _ypos) return false;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	if (m_board[_ypos][_xpos] != eInGameObjType::Balloon 
		&& m_board[_ypos][_xpos] != eInGameObjType::Block_Destructible)
	{
		CLayer* layer = scene->FindLayer("Event");

		if (layer)
		{
			m_board[_ypos][_xpos] = _type;
			if (_obj != nullptr)
				layer->AddObj(_obj);
		}
		return true;
	}

	return false;
}

void CBoard::RemoveObj(D2D1_RECT_F _rect)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	if (m_mapData.gridX <= x) return;
	if (m_mapData.gridY <= y) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer("Block");
	CObj* obj = layer->FindObj(_rect);
	if (obj != nullptr && m_board[y][x] != eInGameObjType::Block_InDestructible) 
		obj->SetAlive(false);

	m_board[y][x] = eInGameObjType::None;
}

void CBoard::RemoveObj(int _xpos, int _ypos, std::string _strLayerKey)
{
	if (m_mapData.gridX <= _xpos) return;
	if (m_mapData.gridY <= _ypos) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer(_strLayerKey);
	CObj* obj = layer->FindObj(_xpos, _ypos);
	
	if (_strLayerKey.compare("Vehicle") == 0)
		((CVehicle*)obj)->SetAvailable(false);
	if (obj != nullptr && m_board[_ypos][_xpos] != eInGameObjType::Block_InDestructible)
		obj->SetAlive(false);

	m_board[_ypos][_xpos] = eInGameObjType::None;
}

bool CBoard::PutSplash(D2D1_RECT_F _rect, std::string _animClipName)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	if (m_mapData.gridX <= x) return false;
	if (m_mapData.gridY <= y) return false;


	if (IsGameObjType(x, y, eInGameObjType::Block_InDestructible))
		return false;
	if (IsGameObjType(x, y, eInGameObjType::Block_Destructible))
	{
		RemoveObj(x, y, "Block");
		return false;
	}
	if (IsGameObjType(x, y, eInGameObjType::Balloon))
	{
		RemoveObj(x, y, "Event");
		return false;
	}

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	 CLayer*  layer = scene->FindLayer("Event");

	if (layer)
	{
		CSplash* splash = new CSplash({
			(float)x * BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)y * BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)x * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)y * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40)
			}, _animClipName);

		layer->AddObj(splash);
	}


	return true;
}

CItem* CBoard::GetItem(D2D1_RECT_F _rect)
{
	// 레이어에서 아이템 die하고  
	int x, y;
	CObj::RectToPos(_rect, x, y);

	CItem* item = m_itemBoard[y][x];
	if (!item)
		return nullptr;
	item->Die();
	m_itemBoard[y][x] = nullptr;

	return item;
}

void CBoard::PutItem(D2D1_RECT_F _rect, CItem* _pItem)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	m_itemBoard[y][x] = _pItem;
}
