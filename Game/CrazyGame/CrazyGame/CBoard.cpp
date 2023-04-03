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
 
CBoard::CBoard()
{
}

CBoard::~CBoard()
{
	// m_board.clear();
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

bool CBoard::IsMovable(int _xpos, int _ypos, bool _isGridPos)
{
	if (_xpos < 0) return false;
	if (_ypos < 0) return false;

	if (_isGridPos == false)
	{
		_xpos /= BOARD_BLOCK_SIZE;
		_ypos /= BOARD_BLOCK_SIZE;
	}

	if (m_mapData.gridX <= _xpos) return false;
	if (m_mapData.gridY <= _ypos) return false;

	return m_board[_ypos][_xpos] == eInGameObjType::None || m_board[_ypos][_xpos] == eInGameObjType::Item;
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

void CBoard::PutObj(int _xpos, int _ypos, CObj* _obj, eInGameObjType _type)
{
	if (m_mapData.gridX <= _xpos) return;
	if (m_mapData.gridY <= _ypos) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	if (m_board[_ypos][_xpos] != eInGameObjType::Balloon)
	{
		CLayer* layer = scene->FindLayer("Event");

		if (layer)
		{
			m_board[_ypos][_xpos] = _type;
			if(_obj != nullptr)
				layer->AddObj(_obj);
		}
	}
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

void CBoard::RemoveObj(int _xpos, int _ypos)
{
	if (m_mapData.gridX <= _xpos) return;
	if (m_mapData.gridY <= _ypos) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer("Block");
	CObj* obj = layer->FindObj(_xpos, _ypos);
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
