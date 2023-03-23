#include "CPlayer.h"
#include "CBitmap.h"
#include "CScene.h"
#include "CInGameScene.h"
#include "CTimer.h"
#include "CAnimation.h"
#include "CAnimationClip.h"
#include "CResourceManager.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Input()
{
	if (m_isDying) return;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_eMoveDir = Dir::Left;
		m_eLastMoveDir = m_eMoveDir;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_eMoveDir = Dir::Right;
		m_eLastMoveDir = m_eMoveDir;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_eMoveDir = Dir::Up;
		m_eLastMoveDir = m_eMoveDir;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_eMoveDir = Dir::Down;
		m_eLastMoveDir = m_eMoveDir;
	}
	else
	{
		m_eMoveDir = Dir::None;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_bFire = true;
	}
}

void CPlayer::Update()
{
	CObj::Update();
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = m_rect.left - stageFrameOffsetX;
	int right = m_rect.right - stageFrameOffsetX;
	int top = m_rect.top - stageFrameOffsetY;
	int bottom = m_rect.bottom - stageFrameOffsetY;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();


	m_prevXPos = m_xpos;
	m_prevYPos = m_ypos;
	m_xpos = left / BOARD_BLOCK_SIZE;
	m_ypos = top / BOARD_BLOCK_SIZE;

	if (m_prevXPos != m_xpos || m_prevYPos != m_ypos)
	{
		auto scene = dynamic_cast<CInGameScene*>(m_pScene);
		scene->m_board->SetInGameObjType(m_prevXPos, m_prevYPos, eInGameObjType::None);
		scene->m_board->SetInGameObjType(m_xpos, m_ypos, eInGameObjType::Character);
	}

	if (m_eMoveDir == Dir::Left)
	{
		// ÇÁ·¹ÀÓ °¡·Î ±æÀÌ stageFrameOffsetX »©ÁÜ
		if (((CInGameScene*)m_pScene)->m_board->IsMovable(left - m_speed * deltaTime, bottom - (BOARD_BLOCK_SIZE * 0.2f), false) 
			&& ((CInGameScene*)m_pScene)->m_board->IsMovable(left - m_speed * deltaTime, top + (BOARD_BLOCK_SIZE * 0.2f), false))
		{
			m_rect.left -= m_speed * deltaTime;
			m_rect.right -= m_speed * deltaTime;
			m_pAnim->SetClip("bazzi_left");
			m_isMoving = true;
		}
	}
	else if (m_eMoveDir == Dir::Right)
	{
		if (((CInGameScene*)m_pScene)->m_board->IsMovable(right + m_speed * deltaTime, bottom - (BOARD_BLOCK_SIZE * 0.2f), false)
			&& ((CInGameScene*)m_pScene)->m_board->IsMovable(right + m_speed * deltaTime, top + (BOARD_BLOCK_SIZE * 0.2f), false))
		{
			m_rect.left += m_speed * deltaTime;
			m_rect.right += m_speed * deltaTime;
			m_pAnim->SetClip("bazzi_right");
			m_isMoving = true;
		}
	}
	else if (m_eMoveDir == Dir::Up)
	{
		if (((CInGameScene*)m_pScene)->m_board->IsMovable(left + (BOARD_BLOCK_SIZE * 0.2f), top - m_speed * deltaTime, false)
			&& ((CInGameScene*)m_pScene)->m_board->IsMovable(right - (BOARD_BLOCK_SIZE * 0.2f), top - m_speed * deltaTime, false))
		{
			m_rect.top -= m_speed * deltaTime;
			m_rect.bottom -= m_speed * deltaTime;
			m_pAnim->SetClip("bazzi_up");
			m_isMoving = true;
		}
	}
	else if (m_eMoveDir == Dir::Down)
	{
		if (((CInGameScene*)m_pScene)->m_board->IsMovable(left + (BOARD_BLOCK_SIZE * 0.2f), bottom + m_speed * deltaTime, false)
			&& ((CInGameScene*)m_pScene)->m_board->IsMovable(right - (BOARD_BLOCK_SIZE * 0.2f), bottom + m_speed * deltaTime, false))
		{
			m_rect.top += m_speed * deltaTime;
			m_rect.bottom += m_speed * deltaTime;
			m_pAnim->SetClip("bazzi_down");
			m_isMoving = true;
		}
	}
	else
		m_isMoving = false;

	if (m_bFire)
	{
		((CInGameScene*)m_pScene)->m_board->PutItem(m_rect, "bubble", eInGameObjType::Balloon);
		m_bFire = false;
	}

#ifdef _DEBUG
	char str[50] = "";
	sprintf_s(str, "%f\n",  deltaTime);
	OutputDebugStringA(str);
#endif
}

void CPlayer::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = nullptr;
	tAnimationFrame* frame = nullptr;

	if (m_isDying == true)
	{
		m_pAnim->SetClip("bazzi_die");
		clip = m_pAnim->GetClip("bazzi_die");
		if (!clip) return;
		frame = clip->GetCurFrame();

		if (clip->IsCurClipEnd())
		{
			m_isAlive = false;
			return;
		}

		_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
			m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			frame->rect);
		return;
	}

	std::string strDir = "";
	switch (m_eLastMoveDir)
	{
	case Dir::Up:
		strDir = "bazzi_up";
		break;
	case Dir::Down:
		strDir = "bazzi_down";
		break;
	case Dir::Left:
		strDir = "bazzi_left";
		break;
	case Dir::Right:
		strDir = "bazzi_right";
		break;
	}

	clip = m_pAnim->GetClip(strDir);
	if (!clip) return;
	
	if (m_isMoving)
	{
		frame = clip->GetCurFrame();
		_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
			m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			frame->rect);
	}
	else
	{
		frame = clip->GetFirstFrame();
		_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
			m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			frame->rect);
	}
}

void CPlayer::Die()
{
}
