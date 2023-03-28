#include "CBubble.h"
#include "CAnimator.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CAnimationClip.h"
#include "CSceneManager.h"
#include "CInGameScene.h"

CBubble::CBubble()
{
}

CBubble::~CBubble()
{
}

void CBubble::Update()
{
	CObj::Update();
	m_elapsedTime += CTimer::GetInst()->GetDeltaTime();
	if (m_elapsedTime >= m_dieTime)
	{
		m_isAlive = false;
	}
}

void CBubble::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = m_pAnim->GetClip("bubble");
	if (!clip) return;
	tAnimationFrame* frame = clip->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}

void CBubble::Die()
{
	CBoard* board = ((CInGameScene*)(CSceneManager::GetInst()->GetCurScene()))->m_board;

	if (board->PutSplash(m_rect, "Explosion_center") == false)
	{
		board->RemoveObj(m_rect);
	}

	D2D1_RECT_F rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left -= BOARD_BLOCK_SIZE;
		rect.right -= BOARD_BLOCK_SIZE;
		if (board->PutSplash(rect, "Explosion_left") == false)
		{
			board->RemoveObj(rect);
			break;
		}

	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left += BOARD_BLOCK_SIZE;
		rect.right += BOARD_BLOCK_SIZE;
		if (board->PutSplash(rect, "Explosion_right") == false)
		{
			board->RemoveObj(rect);
			break;
		}
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top -= BOARD_BLOCK_SIZE;
		rect.bottom -= BOARD_BLOCK_SIZE;
		if (board->PutSplash(rect, "Explosion_up") == false)
		{
			board->RemoveObj(rect);
			break;
		}
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top += BOARD_BLOCK_SIZE;
		rect.bottom += BOARD_BLOCK_SIZE;
		if (board->PutSplash(rect, "Explosion_down") == false)
		{
			board->RemoveObj(rect);
			break;
		}
	}
}
 