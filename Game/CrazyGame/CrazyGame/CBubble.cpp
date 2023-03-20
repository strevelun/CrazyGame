#include "CBubble.h"
#include "CAnimation.h"
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
		Die();
		m_isAlive = false;
	}
}

void CBubble::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = m_pAnim->GetClip("bubble");
	if (!clip) return;
	tAnimationFrame* frame = clip->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->idx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}

void CBubble::Die()
{
	CBoard* board = ((CInGameScene*)(CSceneManager::GetInst()->GetScene()))->m_board;

	board->PutSplash(m_rect, "Explosion_center");

	D2D1_RECT_F rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left -= BOARD_BLOCK_SIZE * i;
		rect.right -= BOARD_BLOCK_SIZE * i;
		board->PutSplash(rect, "Explosion_left");
		rect = m_rect;
		rect.left += BOARD_BLOCK_SIZE * i;
		rect.right += BOARD_BLOCK_SIZE * i;
		board->PutSplash(rect, "Explosion_right");
		rect = m_rect;
		rect.top -= BOARD_BLOCK_SIZE * i;
		rect.bottom -= BOARD_BLOCK_SIZE * i;
		board->PutSplash(rect, "Explosion_up");
		rect = m_rect;
		rect.top += BOARD_BLOCK_SIZE * i;
		rect.bottom += BOARD_BLOCK_SIZE * i;
		board->PutSplash(rect, "Explosion_down");
		rect = m_rect;
	}

}
 