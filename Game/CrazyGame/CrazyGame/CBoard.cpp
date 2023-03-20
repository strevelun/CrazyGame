#include "CBoard.h"
#include "CInGameScene.h"
#include "CSceneManager.h"
#include "CBubble.h"
#include "CResourceManager.h"
#include "CAnimation.h"
#include "CAnimationClip.h"

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
}

bool CBoard::IsMovable(int _x, int _y)
{
	if (_x < 0) return false;
	if (_y < 0) return false;

	_x /= BOARD_BLOCK_SIZE;
	_y /= BOARD_BLOCK_SIZE;

	if (m_mapData.gridX <= _x) return false;
	if (m_mapData.gridY <= _y) return false;

	return m_board[_y][_x] != eInGameObjType::Block;
}

void CBoard::PutBubble(D2D1_RECT_F _rect)
{
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = (_rect.left - stageFrameOffsetX) + BOARD_BLOCK_SIZE / 2;
	int bottom = _rect.top - stageFrameOffsetY + BOARD_BLOCK_SIZE / 2;

	int x = left / BOARD_BLOCK_SIZE;
	int y = bottom / BOARD_BLOCK_SIZE;

	if (m_mapData.gridX <= x) return;
	if (m_mapData.gridY <= y) return;

	CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetScene();

	if (m_board[y][x] != eInGameObjType::Balloon)
	{
		CLayer* layer = scene->FindLayer("Event");
		if (layer)
		{
			m_board[y][x] = eInGameObjType::Balloon;
			CBubble* bubble = new CBubble();
			CAnimation* anim = new CAnimation;
			CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("bubble");
			animClip->SetFrametimeLimit(0.25f);
			CAnimationClip* newAnimClip = new CAnimationClip(*animClip);

			anim->AddClip("bubble", newAnimClip);
			anim->SetClip("bubble");
			bubble->SetAnimation(anim);

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

void CBoard::RemoveObj(D2D1_RECT_F _rect)
{
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = _rect.left - stageFrameOffsetX;
	int bottom = _rect.top - stageFrameOffsetY + BOARD_BLOCK_SIZE / 2;

	int x = left / BOARD_BLOCK_SIZE;
	int y = bottom / BOARD_BLOCK_SIZE;

	if (m_mapData.gridX <= x) return;
	if (m_mapData.gridY <= y) return;

	m_board[y][x] = eInGameObjType::None;
}
