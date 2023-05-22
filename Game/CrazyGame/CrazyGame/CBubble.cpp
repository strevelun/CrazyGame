#include "CBubble.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CBoss.h"

CBubble::CBubble(const D2D1_RECT_F& _rect, eInGameObjType _type) : CMoveObj(_rect)
{	
	m_animClip = *(CResourceManager::GetInst()->GetAnimationClip(L"bubble"));
	m_animClip.SetFrametimeLimit(0.25f);

	m_anim.AddClip(L"bubble", &m_animClip);
	m_anim.SetClip(L"bubble");

	m_eType = _type;
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

	m_anim.Update();

	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_dieTime)
	{
		m_isAlive = false;
	}

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	// ¹°Ç³¼±ÀÌ °È¾îÂ÷ÀÏ¶§
	if (m_bMoving)
	{
		D2D1_RECT_F rect = m_rect;


		switch (m_eMovingDir)
		{
		case eDir::Left:
			x = -1;
			break;
		case eDir::Right:
			x = 1;
			break;
		case eDir::Up:
			y = -1;
			break;
		case eDir::Down:
			y = 1;
			break;
		}


		if (!pBoard->IsMovable(m_cellXPos + x, m_cellYPos + y))
		{
			m_eMovingDir = eDir::None;
			m_bMoving = false;
			m_rect.left = m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX;
			m_rect.right = m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX;
			m_rect.top = m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
			m_rect.bottom = m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY;
			return;
		}

		rect.left += speed * deltaTime * x;
		rect.right += speed * deltaTime * x;
		rect.top += speed * deltaTime * y;
		rect.bottom += speed * deltaTime * y;

		m_prevCellPos.x = m_cellXPos;
		m_prevCellPos.y = m_cellYPos;

		m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
		m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

		pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
		pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);
		m_rect = rect;
	} 
	else if (m_bBounceMoving)
	{
		speed = 10;
		double radian = m_angle * PI / 180.0;
		double dx = speed * cos(radian);
		double dy = 20 * sin(radian) - m_gravity * CTimer::GetInst()->GetDeltaTime();

		D2D1_RECT_F rect = m_rect;


		switch (m_eMovingDir)
		{
		case eDir::Left:
			x = -1;
			break;
		case eDir::Right:
			x = 1;
			break;
		case eDir::Up:
			y = -1;
			break;
		case eDir::Down:
			y = 1;
			break;
		}

		if (!pBoard->IsMovable(m_cellXPos + x, m_cellYPos + y))
		{
			m_eMovingDir = eDir::None;
			m_bBounceMoving = false;
			m_rect.left = m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX;
			m_rect.right = m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX;
			m_rect.top = m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
			m_rect.bottom = m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY;
			return;
		}

		rect.left += dx * x;
		rect.right += dx * x;
		rect.top += dy * y;
		rect.bottom += dy * y;

		m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
		m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

		if (m_cellXPos != m_prevCellXPos || m_cellYPos != m_prevCellYPos)
		{
			pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
			pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);
		}

		m_rect = rect;
	}

	// ¹°Ç³¼±ÀÌ º¸½º¿Í ºÎµúÈ÷¸é
	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Boss))
	{
		m_isAlive = false;
		m_bMoving = false;
	}
}

void CBubble::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_anim.Render(_pRenderTarget, m_rect);
}

void CBubble::Move(eDir _eDir)
{
	m_bMoving = true;
	m_eMovingDir = _eDir;
}

void CBubble::BounceMove(eDir _eDir)
{
	m_bBounceMoving = true;
	m_eMovingDir = _eDir;
}

void CBubble::Die()
{

	CBoard* board = ((CInGameScene*)(CSceneManager::GetInst()->GetCurScene()))->m_board;
	int xpos, ypos;

	board->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::None);

	bool hitBoss = false;
	int hitBossCellXPos = m_cellXPos, hitBossCellYPos = m_cellYPos;

	board->PutSplash(m_rect, L"Explosion_center");

	D2D1_RECT_F rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left -= BOARD_BLOCK_SIZE;
		rect.right -= BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (!hitBoss && board->IsGameObjType(m_cellXPos - i, m_cellYPos, eInGameObjType::Boss))
		{
			hitBossCellXPos = m_cellXPos - i;
			hitBoss = true;
		}

		if (board->PutSplash(rect, L"Explosion_left") == false)
			break;
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.left += BOARD_BLOCK_SIZE;
		rect.right += BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (!hitBoss && board->IsGameObjType(m_cellXPos + i, m_cellYPos, eInGameObjType::Boss))
		{
			hitBossCellXPos = m_cellXPos + i;
			hitBoss = true;
		}

		if (board->PutSplash(rect, L"Explosion_right") == false)
			break;
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top -= BOARD_BLOCK_SIZE;
		rect.bottom -= BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (!hitBoss && board->IsGameObjType(m_cellXPos, m_cellYPos - i, eInGameObjType::Boss))
		{
			hitBossCellYPos = m_cellYPos - i;
			hitBoss = true;
		}

		if (board->PutSplash(rect, L"Explosion_up") == false)
			break;
	}

	rect = m_rect;

	for (int i = 1; i <= m_splashLength; i++)
	{
		rect.top += BOARD_BLOCK_SIZE;
		rect.bottom += BOARD_BLOCK_SIZE;
		CObj::RectToPos(rect, xpos, ypos);

		if (!hitBoss && board->IsGameObjType(m_cellXPos, m_cellYPos + i, eInGameObjType::Boss))
		{
			hitBossCellYPos = m_cellYPos + i;
			hitBoss = true;
		}

		if (board->PutSplash(rect, L"Explosion_down") == false)
			break;
	}

	eInGameObjType eType = m_pOwner->GetType();

	if(eType == eInGameObjType::Character)
		((CPlayer*)m_pOwner)->ReduceCurBubble(1);

	if (hitBoss && eType == eInGameObjType::Character)
	{
		CBoss* pBoss = (CBoss*)board->GetObjTypeInMoveObjBoard(hitBossCellXPos, hitBossCellYPos);
		if(pBoss->GetState() != State::Hit)
			pBoss->Hit(m_attackPower);
	}
}
 