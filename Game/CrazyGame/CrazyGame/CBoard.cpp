#include "CBoard.h"
#include "CInGameScene.h"
#include "CSceneManager.h"
#include "CBubble.h"
#include "CResourceManager.h"
#include "CAnimation.h"
#include "CAnimationClip.h"
#include "CSplash.h"
#include "CPlayer.h"



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

	return m_board[_ypos][_xpos] != eInGameObjType::Block;
}

void CBoard::PutItem(D2D1_RECT_F _rect, std::string _animClipName, eInGameObjType _type)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

#ifdef _DEBUG
	char str[50] = "";
	sprintf_s(str, "%d, %d에 물풍선 놓음\n",x, y );
	OutputDebugStringA(str);
#endif

	if (m_mapData.gridX <= x) return;
	if (m_mapData.gridY <= y) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	if (m_board[y][x] != eInGameObjType::Balloon)
	{
		CLayer* layer = scene->FindLayer("Event");
		if (layer)
		{
			m_board[y][x] = _type;
			CBubble* bubble = new CBubble(); // T
			CAnimation* anim = new CAnimation;
			CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(_animClipName);
			animClip->SetFrametimeLimit(0.25f);
			CAnimationClip* newAnimClip = new CAnimationClip(*animClip);

			anim->AddClip(_animClipName, newAnimClip);
			anim->SetClip(_animClipName);
			bubble->SetAnimation(anim);

			bubble->SetRect({
				(float)x * BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
				(float)y * BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40),
				(float)x * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
				(float)y * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40)
				});
			layer->AddObj(bubble);
		}
	}
}

void CBoard::RemoveObj(D2D1_RECT_F _rect)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	if (m_mapData.gridX <= x) return;
	if (m_mapData.gridY <= y) return;

	m_board[y][x] = eInGameObjType::None;
	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer("Block");
	CObj* obj = layer->FindObj(_rect);
	if (obj != nullptr) obj->SetAlive(false);
}

bool CBoard::PutSplash(D2D1_RECT_F _rect, std::string _animClipName)
{
	int x, y;
	CObj::RectToPos(_rect, x, y);

	if (m_mapData.gridX <= x) return false;
	if (m_mapData.gridY <= y) return false;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

	CLayer* layer = scene->FindLayer("Character");

	if (IsMovable(x, y, true) == false)
		return false;

	if (m_moveObjBoard[y][x] == eInGameObjType::Character)
	{
		CPlayer* player = dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetCurScene())->GetPlayer();
		if(player) 
			player->SetIsDying(true);
	}

	layer = scene->FindLayer("Event");

	if (m_board[y][x] == eInGameObjType::Balloon)
	{
		CObj* obj = layer->FindObj(_rect);
		if (obj) obj->SetAlive(false);
		return false;
	}


	if (layer)
	{
		CSplash* splash = new CSplash();
		CAnimation* anim = new CAnimation;
		CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(_animClipName);
		animClip->SetFrametimeLimit(0.1f);
		CAnimationClip* newAnimClip = new CAnimationClip(*animClip);
		splash->SetClipName(_animClipName);
		anim->AddClip(_animClipName, newAnimClip);
		anim->SetClip(_animClipName);
		splash->SetAnimation(anim);

		splash->SetRect({
			(float)x * BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)y * BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)x * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)y * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40)
			});
		layer->AddObj(splash);
	}

	return true;
}
