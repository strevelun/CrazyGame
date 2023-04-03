#include "CBubble.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"


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

	m_animator.Update();

	m_elapsedTime += CTimer::GetInst()->GetDeltaTime();
	if (m_elapsedTime >= m_dieTime)
	{
		m_isAlive = false;
	}
}

void CBubble::Render(ID2D1RenderTarget* _pRenderTarget)
{;
	tAnimationFrame* frame = m_animClip.GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
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
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_InDestructible))
			break;
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_Destructible))
		{
			board->RemoveObj(xpos, ypos);
			break;
		}
		board->PutSplash(rect, "Explosion_left");
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left += BOARD_BLOCK_SIZE;
		rect.right += BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_InDestructible))
			break;
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_Destructible))
		{
			board->RemoveObj(xpos, ypos);
			break;
		}
		board->PutSplash(rect, "Explosion_right");
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top -= BOARD_BLOCK_SIZE;
		rect.bottom -= BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_InDestructible))
			break;
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_Destructible))
		{
			board->RemoveObj(xpos, ypos);
			break;
		}
		board->PutSplash(rect, "Explosion_up");
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top += BOARD_BLOCK_SIZE;
		rect.bottom += BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_InDestructible))
			break;
		if (board->IsGameObjType(xpos, ypos, eInGameObjType::Block_Destructible))
		{
			board->RemoveObj(xpos, ypos);
			break;
		}
		board->PutSplash(rect, "Explosion_down");
	}
}
 