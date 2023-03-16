#include "CPlayer.h"
#include "CBitmap.h"
#include "CScene.h"
#include "CInGameScene.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Input()
{


	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_eMoveDir = Dir::Left;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_eMoveDir = Dir::Right;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_eMoveDir = Dir::Up;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_eMoveDir = Dir::Down;
	}
	else
		m_eMoveDir = Dir::None;
}

void CPlayer::Update()
{
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = m_rect.left - stageFrameOffsetX;
	int right = m_rect.right - stageFrameOffsetX;
	int top = m_rect.top - stageFrameOffsetY;
	int bottom = m_rect.bottom - stageFrameOffsetY;

	if (m_eMoveDir == Dir::Left)
	{
		int a = (m_rect.left - m_speed);
		// ÇÁ·¹ÀÓ °¡·Î ±æÀÌ stageFrameOffsetX »©ÁÜ
		if (((CInGameScene*)m_pScene)->IsMovable(left - m_speed, bottom) && ((CInGameScene*)m_pScene)->IsMovable(left - m_speed, top))
		{
			m_rect.left -= m_speed;
			m_rect.right -= m_speed;
		}
	}
	else if (m_eMoveDir == Dir::Right)
	{
		if (((CInGameScene*)m_pScene)->IsMovable(right + m_speed, bottom) && ((CInGameScene*)m_pScene)->IsMovable(right + m_speed, top))
		{
			m_rect.left += m_speed;
			m_rect.right += m_speed;
		}
	}
	else if (m_eMoveDir == Dir::Up)
	{
		if (((CInGameScene*)m_pScene)->IsMovable(left, top - m_speed) && ((CInGameScene*)m_pScene)->IsMovable(right, top - m_speed))
		{
			m_rect.top -= m_speed;
			m_rect.bottom -= m_speed;
		}
	}
	else if (m_eMoveDir == Dir::Down)
	{
		if (((CInGameScene*)m_pScene)->IsMovable(left, bottom + m_speed ) && ((CInGameScene*)m_pScene)->IsMovable(right, bottom + m_speed))
		{
			m_rect.top += m_speed;
			m_rect.bottom += m_speed;
		}
	}

#ifdef _DEBUG
	char str[50] = "";
	sprintf_s(str, "%f, %f, %f, %f\n", m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	OutputDebugStringA(str);
#endif
}

void CPlayer::Render(ID2D1RenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(m_pBitmap->GetBitmap(), m_rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_sprite->rect);
}
