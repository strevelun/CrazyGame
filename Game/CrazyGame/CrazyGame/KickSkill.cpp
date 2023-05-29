#include "KickSkill.h"
#include "CBoard.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CTimer.h"
#include "CBubble.h"

KickSkill::KickSkill(CBubble* _pOwner, eDir _eDir) : BubbleSkill(_eDir)
{
	m_pOwner = _pOwner;
}

KickSkill::~KickSkill()
{
}

void KickSkill::Update()
{
	CBoard* pBoard = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	float speed = 1000;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	CBubble* bubble = (CBubble*)m_pOwner;

	D2D1_RECT_F rect = bubble->m_rect;

	if (!pBoard->IsMovable(bubble->m_cellXPos + m_dirX, bubble->m_cellYPos + m_dirY))
	{
		m_eMovingDir = eDir::None;
		m_skillEnd = true;
		bubble->m_rect.left = bubble->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX;
		bubble->m_rect.right = bubble->m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX;
		bubble->m_rect.top = bubble->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		bubble->m_rect.bottom = bubble->m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY;
		return;
	}

	rect.left += speed * deltaTime * m_dirX;
	rect.right += speed * deltaTime * m_dirX;
	rect.top += speed * deltaTime * m_dirY;
	rect.bottom += speed * deltaTime * m_dirY;

	m_prevCellPos.x = bubble->m_cellXPos;
	m_prevCellPos.y = bubble->m_cellYPos;

	bubble->m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	bubble->m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
	pBoard->SetInGameObjType(bubble->m_cellXPos, bubble->m_cellYPos, eInGameObjType::Balloon);
	bubble->m_rect = rect;
}
