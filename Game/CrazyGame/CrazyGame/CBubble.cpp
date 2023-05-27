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
	CBoard* pBoard = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board;
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	float speed = 7;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	D2D1_RECT_F rect = m_rect;

	if(m_curThrow >= m_throwLimit) // limitÀ» ³ÑÀ¸¸é ÇÑÄ­¾¿ Âø·úÁöÁ¡ Ã¼Å©
	{
		//if (pBoard->IsMovable(m_cellXPos, m_cellYPos)) // ´øÁú¶© ¹°Ç³¼± °ãÄ¡±â °¡´ÉÀÌ¶ó¼­ »ç¿ë¾ÈÇÔ
		if(pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon) 
			|| pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::None)
			|| pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Item))
		{
			m_eMovingDir = eDir::None;
			m_bBounceMoving = false;
			pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);

			m_rect.left = m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX;
			m_rect.right = m_rect.left + BOARD_BLOCK_SIZE;
			m_rect.top = m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
			m_rect.bottom = m_rect.top + BOARD_BLOCK_SIZE;
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
			float radian = m_angle * PI / 180.0;
			float velocityY = 3 * std::sin(radian);
			ballX = speed;
			ballY = -velocityY + m_ballTime * 30;
			if (m_rect.bottom >= m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY)
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

	rect.left += ballX * m_dirX;
	rect.right += ballX * m_dirX;

	m_prevCellPos.x = m_cellXPos;
	m_prevCellPos.y = m_cellYPos;

	m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	if (m_cellYPos < 0)
	{
		m_cellYPos = 12;
		rect.top = m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.bottom = rect.top + BOARD_BLOCK_SIZE;
	}
	else if (m_cellYPos > 12)
	{
		m_cellYPos = 0;
		rect.top = m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.bottom = rect.top + BOARD_BLOCK_SIZE;
	}
	else if (m_cellXPos < 0)
	{
		m_cellXPos = 14;
		rect.left = m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.right = rect.left + BOARD_BLOCK_SIZE;
	}
	else if (m_cellXPos > 14)
	{
		m_cellXPos = 0;		
		rect.left = m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		rect.right = rect.left + BOARD_BLOCK_SIZE;
	}

	if (m_prevCellPos.x != m_cellXPos || m_prevCellPos.y != m_cellYPos)
		m_curThrow++;

	//pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
	//pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);



	m_rect = rect;
}

void CBubble::KickSkill()
{
	CBoard* pBoard = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board;
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	float speed = 1000;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();
	D2D1_RECT_F rect = m_rect;

	if (!pBoard->IsMovable(m_cellXPos + m_dirX, m_cellYPos + m_dirY))
	{
		m_eMovingDir = eDir::None;
		m_bMoving = false;
		m_rect.left = m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX;
		m_rect.right = m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX;
		m_rect.top = m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY;
		m_rect.bottom = m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY;
		return;
	}

	rect.left += speed * deltaTime * m_dirX;
	rect.right += speed * deltaTime * m_dirX;
	rect.top += speed * deltaTime * m_dirY;
	rect.bottom += speed * deltaTime * m_dirY;

	m_prevCellPos.x = m_cellXPos;
	m_prevCellPos.y = m_cellYPos;

	m_cellXPos = ((rect.right - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = ((rect.bottom - BOARD_BLOCK_SIZE / 2) - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	pBoard->SetInGameObjType(m_prevCellPos.x, m_prevCellPos.y, eInGameObjType::None);
	pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);
	m_rect = rect;
}

void CBubble::SetDir(eDir _eDir)
{
	m_dirX = 0; m_dirY = 0;

	switch (_eDir)
	{
	case eDir::Left:
		m_dirX = -1;
		break;
	case eDir::Right:
		m_dirX = 1;
		break;
	case eDir::Up:
		m_dirY = -1;
		break;
	case eDir::Down:
		m_dirY = 1;
		break;
	}
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

	SetDir(_eDir);
}

void CBubble::BounceMove(eDir _eDir)
{
   	m_bBounceMoving = true;
	m_eMovingDir = _eDir;

	//m_dir.x = 1;
	//m_dir.y = 0;
	if (_eDir == eDir::Left || _eDir == eDir::Right)
	{
		m_rect.top -= 20;
		m_rect.bottom -= 20;
		m_eThrowState = eThrowState::InAir;
	}

	SetDir(_eDir);
	CBoard* pBoard = ((CInGameScene*)(CSceneManager::GetInst()->GetCurScene()))->m_board;
	pBoard->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::None);
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
 