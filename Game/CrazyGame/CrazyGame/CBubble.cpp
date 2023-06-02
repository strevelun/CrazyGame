#include "CBubble.h"
#include "Setting.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CTimer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CBoss.h"
#include "KickSkill.h"
#include "BounceMoveSkill.h"

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

	
	if (m_pSkill != nullptr)
	{
		if (m_pSkill->IsSkillEnd())
		{
			delete m_pSkill;
			m_pSkill = nullptr;
		}
		else
			m_pSkill->Update();
	}

	// 물풍선이 보스와 부딪히면
	CBoss* boss = (CBoss*)(pBoard->GetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos));
	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Boss))
	{
		if (boss && boss->GetState() != State::TrappedInBubble)
		{
			m_isAlive = false;
			delete m_pSkill;
			m_pSkill = nullptr;
		}
	}
}

void CBubble::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_anim.Render(_pRenderTarget, m_rect);
}

void CBubble::Move(eDir _eDir)
{
	m_pSkill = new KickSkill(this, _eDir);
}

void CBubble::BounceMove(eDir _eDir)
{
	if (_eDir == eDir::Left || _eDir == eDir::Right)
	{
		m_rect.top -= 20;
		m_rect.bottom -= 20;
	}

	m_pSkill = new BounceMoveSkill(this, _eDir);
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

	board->PutSplash(m_rect, L"Explosion_center", m_pOwner);

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

		if (board->PutSplash(rect, L"Explosion_left", m_pOwner) == false)
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

		if (board->PutSplash(rect, L"Explosion_right", m_pOwner) == false)
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

		if (board->PutSplash(rect, L"Explosion_up", m_pOwner) == false)
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

		if (board->PutSplash(rect, L"Explosion_down", m_pOwner) == false)
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
 