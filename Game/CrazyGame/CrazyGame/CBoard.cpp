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
	for (u_int i = 0; i < m_mapData.gridY; i++)
		m_board[i].resize(m_mapData.gridX);

	m_moveObjBoard.resize(m_mapData.gridY);
	for (u_int i = 0; i < m_mapData.gridY; i++)
		m_moveObjBoard[i].resize(m_mapData.gridX);

	m_itemBoard.resize(m_mapData.gridY);
	for (u_int i = 0; i < m_mapData.gridY; i++)
		m_itemBoard[i].resize(m_mapData.gridX);
}

bool CBoard::IsMovable(int _cellXPos, int _cellYPos, CVehicle* _vehicle)
{
	if (_cellXPos < 0 || _cellYPos < 0)  return false;
	if (m_mapData.gridX <= _cellXPos)  return false;
	if (m_mapData.gridY <= _cellYPos)  return false;

	if (_vehicle && _vehicle->GetName().compare(L"UFO") == 0
		&& m_board[_cellYPos][_cellXPos] != eInGameObjType::Block_InDestructible)
		return true;

	if (m_board[_cellYPos][_cellXPos] == eInGameObjType::Block_Destructible || m_board[_cellYPos][_cellXPos] == eInGameObjType::Block_InDestructible
		|| m_board[_cellYPos][_cellXPos] == eInGameObjType::Balloon)
		return false;

	return true;
}

bool CBoard::IsGameObjType(int _cellXPos, int _cellYPos, eInGameObjType _type)
{

	if (m_mapData.gridX <= _cellXPos) return false;
	if (m_mapData.gridY <= _cellYPos) return false;

	if (_type == eInGameObjType::Character || _type == eInGameObjType::Monster
		|| _type == eInGameObjType::Boss)
	{
		if (m_moveObjBoard[_cellYPos][_cellXPos] == nullptr) return false;
		return m_moveObjBoard[_cellYPos][_cellXPos]->GetType() == _type;
	}
	else
		return m_board[_cellYPos][_cellXPos] == _type;
}

bool CBoard::PutObj(int _cellXPos, int _cellYPos, CGameObj* _obj, eInGameObjType _type)
{
	if (m_mapData.gridX <= _cellXPos) return false;
	if (m_mapData.gridY <= _cellYPos) return false;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	if (_type == eInGameObjType::Block_Destructible || _type == eInGameObjType::None)
	{
		m_board[_cellYPos][_cellXPos] = _type;
		return true;
	}

	if (m_board[_cellYPos][_cellXPos] != eInGameObjType::Balloon 
		&& m_board[_cellYPos][_cellXPos] != eInGameObjType::Block_Destructible)
	{
		CLayer* layer = scene->FindLayer(L"Block");

		if (layer)
		{
			m_board[_cellYPos][_cellXPos] = _type;
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

	CLayer* layer = scene->FindLayer(L"Block");
	CObj* obj = layer->FindObj(_rect);
	if (obj != nullptr && m_board[y][x] != eInGameObjType::Block_InDestructible) 
		obj->SetAlive(false);

	m_board[y][x] = eInGameObjType::None;
}

void CBoard::RemoveObj(int _cellXPos, int _cellYPos, std::wstring _strLayerKey, eInGameObjType _objType)
{
	if (m_mapData.gridX <= _cellXPos) return;
	if (m_mapData.gridY <= _cellYPos) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer(_strLayerKey);
	CObj* obj = layer->FindGameObj(_cellXPos, _cellYPos); // 만약 물풍선 위에 우주선을 타고 있으면 물풍선밖에 찾지 않는다.
	
	if (obj != nullptr && m_board[_cellYPos][_cellXPos] != eInGameObjType::Block_InDestructible)
	{
		if (_objType == obj->GetType())
		{
			obj->SetAlive(false);
			if (obj->GetType() == eInGameObjType::Item)
				m_itemBoard[_cellYPos][_cellXPos] = nullptr;
		}
	}

	m_board[_cellYPos][_cellXPos] = eInGameObjType::None;
}

bool CBoard::PutSplash(D2D1_RECT_F _rect, std::wstring _animClipName, CMoveObj* _pOwner)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	return PutSplash(x, y, _animClipName, _pOwner);
}

bool CBoard::PutSplash(u_int _cellXPos, u_int _cellYPos, std::wstring _animClipName, CMoveObj* _pOwner)
{
	if (m_mapData.gridX <= _cellXPos) return false;
	if (m_mapData.gridY <= _cellYPos) return false;

	if (IsGameObjType(_cellXPos, _cellYPos, eInGameObjType::Block_InDestructible))
		return false;
	if (IsGameObjType(_cellXPos, _cellYPos, eInGameObjType::Block_Destructible))
	{
		RemoveObj(_cellXPos, _cellYPos, L"Block", eInGameObjType::Block_Destructible);
		return false;
	}
	if (IsGameObjType(_cellXPos, _cellYPos, eInGameObjType::Balloon))
	{
		RemoveObj(_cellXPos, _cellYPos, L"Block", eInGameObjType::Balloon);
		return false;
	}

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer(L"Event");

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	if (layer)
	{
		CSplash* splash = new CSplash({
			(float)_cellXPos* BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)_cellYPos* BOARD_BLOCK_SIZE + stageFrameOffsetY,
			(float)_cellXPos* BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)_cellYPos* BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY
			}, _animClipName, _pOwner);

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

CItem* CBoard::GetItem(u_int _cellXPos, u_int _cellYPos)
{
	CItem* item = m_itemBoard[_cellYPos][_cellXPos];
	if (!item)
		return nullptr;
	item->Die();
	m_itemBoard[_cellYPos][_cellXPos] = nullptr;

	return item;
}

void CBoard::PutItem(D2D1_RECT_F _rect, CItem* _pItem)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	m_itemBoard[y][x] = _pItem;
}
