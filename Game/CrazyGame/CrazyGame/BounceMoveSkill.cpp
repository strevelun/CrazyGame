#include "BounceMoveSkill.h"
#include "CBoard.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CTimer.h"
#include "CBubble.h"

BounceMoveSkill::BounceMoveSkill(CBubble* _pOwner, eDir _eDir) : BubbleSkill(_eDir)
{
	m_eThrowState = eThrowState::InAir;
	m_pOwner = _pOwner;
}

BounceMoveSkill::~BounceMoveSkill()
{
}

void BounceMoveSkill::Update()
{
	CBoard* pBoard = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	float speed = 7;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	CBubble* bubble = (CBubble*)m_pOwner;

	D2D1_RECT_F rect = bubble->m_rect;

	if (m_curThrow >= m_throwLimit) // limitÀ» ³ÑÀ¸¸é ÇÑÄ­¾¿ Âø·úÁöÁ¡ Ã¼Å©
	{
		//if (pBoard->IsMovable(m_cellXPos, m_cellYPos)) // ´øÁú¶© ¹°Ç³¼± °ãÄ¡±â °¡´ÉÀÌ¶ó¼­ »ç¿ë¾ÈÇÔ
		if (pBoard->IsGameObjType(bubble->m_cellXPos, bubble->m_cellYPos, eInGameObjType::Balloon)
			|| pBoard->IsGameObjType(bubble->m_cellXPos, bubble->m_cellYPos, eInGameObjType::None)
			|| pBoard->IsGameObjType(bubble->m_cellXPos, bubble->m_cellYPos, eInGameObjType::Item))
		{
			m_eMovingDir = eDir::None;
			m_skillEnd = true;
			pBoard->SetInGameObjType(bubble->m_cellXPos, bubble->m_cellYPos, eInGameObjType::Balloon);

			bubble->m_rect.left = (FLOAT)bubble->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX;
			bubble->m_rect.right = (FLOAT)bubble->m_rect.left + BOARD_BLOCK_SIZE;
			bubble->m_rect.top = (FLOAT)bubble->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
			bubble->m_rect.bottom = (FLOAT)bubble->m_rect.top + BOARD_BLOCK_SIZE;
			return;
		}
	}

	float ballX = speed;
	float ballY;

	if (m_eMovingDir == eDir::Left || m_eMovingDir == eDir::Right)
	{
		if (m_curThrow == 4 && m_eThrowState == eThrowState::InAir)
		{
			rect.top += 20;
			rect.bottom += 20;
			m_eThrowState = eThrowState::Bounce;
		}

		if (m_curThrow >= 5)
		{
			float radian = m_angle * (float)PI / 180.0f;
			float velocityY = 3 * std::sin(radian);
			ballX = speed;
			ballY = -velocityY + m_ballTime * 30;
			if (bubble->m_rect.bottom >= bubble->m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY)
				m_ballTime = 0.0f;
			m_ballTime += deltaTime;

			m_dirY = 1;
			rect.top += ballY * m_dirY;
			rect.bottom += ballY * m_dirY;
		}
	}
	else
	{
		rect.top += speed * m_dirY;
		rect.bottom += speed * m_dirY;
	}

	//rect.top += ballY * m_dirY;
	//rect.bottom += ballY * m_dirY;


	rect.left += ballX * m_dirX;
	rect.right += ballX * m_dirX;

	m_prevCellPos.x = bubble->m_cellXPos;
	m_prevCellPos.y = bubble->m_cellYPos;

	bubble->m_cellXPos = (((int)rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	bubble->m_cellYPos = (((int)rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	if (bubble->m_cellYPos < 0)
	{
		bubble->m_cellYPos = 12;
		rect.top = (FLOAT)bubble->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.bottom = (FLOAT)rect.top + BOARD_BLOCK_SIZE;
	}
	else if (bubble->m_cellYPos > 12)
	{
		bubble->m_cellYPos = 0;
		rect.top = (FLOAT)bubble->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.bottom = (FLOAT)rect.top + BOARD_BLOCK_SIZE;
	}
	else if (bubble->m_cellXPos < 0)
	{
		bubble->m_cellXPos = 14;
		rect.left = (FLOAT)bubble->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.right = (FLOAT)rect.left + BOARD_BLOCK_SIZE;
	}
	else if (bubble->m_cellXPos > 14)
	{
		bubble->m_cellXPos = 0;
		rect.left = (FLOAT)bubble->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.right = (FLOAT)rect.left + BOARD_BLOCK_SIZE;
	}

	/*
	if (bubble->m_cellYPos < 0)		bubble->m_cellYPos = 12;
	if (bubble->m_cellYPos > 12)	bubble->m_cellYPos = 0;
	if (bubble->m_cellXPos < 0)		bubble->m_cellXPos = 14;
	if (bubble->m_cellXPos > 14)	bubble->m_cellXPos = 0;

	rect.top = bubble->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
	rect.bottom = rect.top + BOARD_BLOCK_SIZE;
	rect.left = bubble->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
	rect.right = rect.left + BOARD_BLOCK_SIZE;
	*/
	if (m_prevCellPos.x != bubble->m_cellXPos || m_prevCellPos.y != bubble->m_cellYPos)
		m_curThrow++;

	bubble->m_rect = rect;
}
