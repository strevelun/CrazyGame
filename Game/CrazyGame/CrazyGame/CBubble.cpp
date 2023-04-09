#include "CBubble.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"

CBubble::CBubble(const D2D1_RECT_F& _rect) : CObj(_rect)
{	
	m_animClip = *(CResourceManager::GetInst()->GetAnimationClip("bubble"));
	m_animClip.SetFrametimeLimit(0.25f);

	m_animator.AddClip("bubble", &m_animClip);
	m_animator.SetClip("bubble");

}

CBubble::~CBubble()
{
}

void CBubble::Update()
{
	// CObj::Update();

	CBoard* pBoard = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board;

	float speed = 1000;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	int x = 0, y = 0;

	m_animator.Update();

	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_dieTime)
	{
		m_isAlive = false;
	}

	if (m_bMoving)
	{
		D2D1_RECT_F rect = m_rect;

		switch (m_eMovingDir)
		{
		case Dir::Left:
			x = -1;
			rect.left += BOARD_BLOCK_SIZE / 2 - 1;
			rect.right += BOARD_BLOCK_SIZE / 2 - 1;
			break;
		case Dir::Right:
			x = 1;
			rect.left -= BOARD_BLOCK_SIZE / 2 + 1;
			rect.right -= BOARD_BLOCK_SIZE / 2 + 1;
			break;
		case Dir::Up:
			y = -1;
			rect.top += BOARD_BLOCK_SIZE / 2 - 1;
			rect.bottom += BOARD_BLOCK_SIZE / 2 - 1;
			break;
		case Dir::Down:
			y = 1;
			rect.top -= BOARD_BLOCK_SIZE / 2 + 1;
			rect.bottom -= BOARD_BLOCK_SIZE / 2 + 1;
			break;
		}
		int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
		int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);

		m_prevCellPos.x = m_cellXPos;
		m_prevCellPos.y = m_cellYPos;

		m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
		m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

		//CObj::RectToPos(rect, m_cellXPos, m_cellYPos);

		pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
		pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);

		if (!pBoard->IsMovable(m_cellXPos + x, m_cellYPos + y))
		{
			m_eMovingDir = Dir::None;
			m_bMoving = false;
			return;
		}

		m_rect.left += speed * deltaTime * x;
		m_rect.right += speed * deltaTime * x;
		m_rect.top += speed * deltaTime * y;
		m_rect.bottom += speed * deltaTime * y;
	}


}

void CBubble::Render(ID2D1RenderTarget* _pRenderTarget)
{;
	tAnimationFrame* frame = m_animClip.GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}

void CBubble::Move(Dir _eDir)
{
	m_bMoving = true;
	m_eMovingDir = _eDir;
}

void CBubble::Die()
{
	CBoard* board = ((CInGameScene*)(CSceneManager::GetInst()->GetCurScene()))->m_board;
	int xpos, ypos;

	board->PutSplash(m_rect, "Explosion_center");

	D2D1_RECT_F rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left -= BOARD_BLOCK_SIZE;
		rect.right -= BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (board->PutSplash(rect, "Explosion_left") == false)
			break;
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left += BOARD_BLOCK_SIZE;
		rect.right += BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);
		
		if (board->PutSplash(rect, "Explosion_right") == false)
			break;
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top -= BOARD_BLOCK_SIZE;
		rect.bottom -= BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (board->PutSplash(rect, "Explosion_up") == false)
			break;
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top += BOARD_BLOCK_SIZE;
		rect.bottom += BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (board->PutSplash(rect, "Explosion_down") == false)
			break;
	}

	m_pPlayer->ReduceCurBubble(1);
}
 