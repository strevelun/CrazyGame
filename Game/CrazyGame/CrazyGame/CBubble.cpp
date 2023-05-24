#include "CBubble.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CBoss.h"

void CBubble::BounceMoveSkill()
{
	CBoard* pBoard = ((CInGameScene*)m_pScene)->m_board;
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	int x = 0, y = 0;
	float speed = 7;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

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

	float radian = m_angle * PI / 180.0;
	float velocityY = 3 * std::sin(radian);
	float ballX = speed;
	float ballY = -velocityY + m_ballTime * 30;
	if (m_rect.bottom >= m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY)
		m_ballTime = 0.0f;
	m_ballTime += deltaTime;

	if (m_eMovingDir == eDir::Left || m_eMovingDir == eDir::Right)
	{
		y = 1;
		rect.top += ballY * y;
		rect.bottom += ballY * y;
	}
	else
	{
		rect.top += ballX * y;
		rect.bottom += ballX * y;
	}

	rect.left += ballX * x;
	rect.right += ballX * x;

	m_prevCellPos.x = m_cellXPos;
	m_prevCellPos.y = m_cellYPos;

	m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
	pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);

	m_rect = rect;
}

void CBubble::KickSkill()
{
	CBoard* pBoard = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board;
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	int x = 0, y = 0;
	float speed = 1000;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();
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

	if (m_bMoving)
	{
		KickSkill();
	} 
	else if (m_bBounceMoving)
	{
		BounceMoveSkill();
	}

	// 물풍선이 보스와 부딪히면
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
 