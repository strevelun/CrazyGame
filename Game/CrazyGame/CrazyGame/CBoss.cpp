#include "CBoss.h"
#include "CBitmap.h"
#include "CBoard.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CAnimationClip.h"
#include "CAnimator.h"
#include "CResourceManager.h"
#include "CTimer.h"
#include "CMonster.h"
#include "CUIHPBar.h"
#include "CUIPanel.h"
#include "CSplash.h"
#include "CBubble.h"

#include <random>

CBoss::CBoss(const D2D1_RECT_F& _rect, eInGameObjType _type) : CMoveObj(_rect)
{
	m_pAnim = new CAnimator;
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Front");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Boss_Front", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Back");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Boss_Back", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Left");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Boss_Left", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Right");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Boss_Right", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Hit");
	animClip->SetFrametimeLimit(0.2f);
	animClip->SetLoop(false);
	m_pAnim->AddClip("Boss_Hit", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Die1");
	animClip->SetFrametimeLimit(3.0f);
	animClip->SetLoop(false);
	m_pAnim->AddClip("Boss_Die1", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Boss_Die2");
	animClip->SetFrametimeLimit(0.2f);
	animClip->SetLoop(false);
	m_pAnim->AddClip("Boss_Die2", animClip);

	m_pAnim->SetClip("Boss_Front");

	

	m_xpos = _rect.left;
	m_ypos = _rect.bottom - (BOARD_BLOCK_SIZE / 2);	
	
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	m_cellXPos = (m_xpos - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = (m_ypos - stageFrameOffsetY) / BOARD_BLOCK_SIZE;



	m_state = State::MoveDown;
	// 플레이어 ready가 끝나면 move하도록

	m_speed = 40.0f;
	m_eType = _type;
}

CBoss::~CBoss()
{
	m_uiHPBar->Die();
}

bool CBoss::Init()
{
	if (SetBossInMoveObjBoard(m_cellXPos, m_cellYPos, this) == false)
	{
		SetBossInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		m_isAlive = false;
		return false;
	}

	D2D1_RECT_F rect = m_rect;
	rect.bottom = m_rect.top - 5;
	rect.top = rect.bottom - 11;

	m_uiHPBar = new CUIHPBar(rect, m_hp);
	// hp bar는 내가 선택한걸로
	m_uiHPBar->SetBitmap(CResourceManager::GetInst()->Load(L"Boss_hp_blue.png"));
	m_uiHPBar->SetHP(m_hp);
	CLayer* layer = m_pScene->FindLayer("MonsterUI");
	layer->AddObj(m_uiHPBar);

	return true;
}

void CBoss::Update()
{
	CObj::Update();

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	m_cellXPos = (m_xpos - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = (m_ypos - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	ChangeState(m_nextState);


	CAnimationClip* clip = nullptr;
	//m_nowState->Update();

	//m_state[m_state]();

	switch (m_state)
	{
	case State::Ready:
		m_nextState = State::MoveDown;

		break;
	case State::MoveLeft:
	case State::MoveRight:
	case State::MoveUp:
	case State::MoveDown:
		MoveState();

		if (m_hp <= 0)
			m_nextState = State::TrappedInBubble;

		break;
	case State::Hit:

		clip = m_pAnim->GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_nextState = State::MoveDown;
			return;
		}
		break;
	case State::TrappedInBubble:
		clip = m_pAnim->GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_nextState = State::Die;
			return;
		}
		break;
	case State::Die:
		SetBossInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		clip = m_pAnim->GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_isAlive = false;
			return;
		}
	break;
	}

	Attack();

	D2D1_RECT_F rect = m_rect;
	rect.bottom = m_rect.top - 5;
	rect.top = rect.bottom - 11;
	m_uiHPBar->SetRect(rect);
}

void CBoss::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.0f, 0.9f, D2D1::Point2F(m_rect.left, m_rect.bottom)));
	m_pAnim->Render(_pRenderTarget, m_rect);
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void CBoss::Hit(u_int _attackPower)
{
	// 랜덤한 포지션에 몬스터 소환

	//for (int i = m_cellYPos; i < m_cellYPos + 4; i++)
	{
	//	for (int j = m_cellXPos; j < m_cellXPos + 3; j++)
		{
			
		}
	}
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	int w = 29, h = 31;
	D2D1_RECT_F rect = D2D1::RectF(
		m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX,
		m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY - h,
		m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX + w,
		m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY
	);

	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();

	CScene* scene = CSceneManager::GetInst()->GetCurScene();
	CLayer* pLayer = scene->FindLayer("Block");

	CMonster* pMonster = new CMonster(rect, eInGameObjType::Monster);
	pLayer->AddObj(pMonster);
	m_nextState = State::Hit;
	m_hp -= _attackPower;

	m_uiHPBar->SetHP(m_hp);
}



bool CBoss::IsMovable(int _cellXPos, int _cellYPos)
{
	if (SetBossInMoveObjBoard(_cellXPos, _cellYPos, this) == false)
	{
		SetBossInMoveObjBoard(_cellXPos, _cellYPos, nullptr);
		return false;
	}

	SetBossInMoveObjBoard(_cellXPos, _cellYPos, nullptr);
	return true;
}

bool CBoss::SetBossInMoveObjBoard(int _cellXPos, int _cellYPos, CMoveObj* _obj)
{
	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board->IsMovable(_cellXPos + j, _cellYPos - i) == false)
				return false;
			board->SetObjTypeInMoveObjBoard(_cellXPos + j, _cellYPos - i, _obj);
		}
	}
	return true;
}

void CBoss::MoveState()
{
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	SetBossInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);

	int x = 0, y = 0;
	if (m_state == State::MoveLeft)
	{
		if (IsMovable(m_cellXPos, m_cellYPos) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		SetBossInMoveObjBoard(m_cellXPos - 1, m_cellYPos, this);

		x = -1;

	}
	else if (m_state == State::MoveRight)
	{
		if (IsMovable(m_cellXPos + 1, m_cellYPos) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		SetBossInMoveObjBoard(m_cellXPos + 1, m_cellYPos, this);

		x = 1;
	}
	else if (m_state == State::MoveUp)
	{
		if (IsMovable(m_cellXPos, m_cellYPos - 1) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		SetBossInMoveObjBoard(m_cellXPos, m_cellYPos - 1, this);

		y = -1;
	}
	else if (m_state == State::MoveDown)
	{
		if (IsMovable(m_cellXPos, m_cellYPos+1) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		SetBossInMoveObjBoard(m_cellXPos, m_cellYPos + 1, this);

		y = 1;
	}


	m_xpos += m_speed * deltaTime * x;
	m_ypos += m_speed * deltaTime * y;

	m_rect.left += m_speed * deltaTime * x;
	m_rect.right += m_speed * deltaTime * x;
	m_rect.top += m_speed * deltaTime * y;
	m_rect.bottom += m_speed * deltaTime * y;
}

void CBoss::ChangeState(State _state)
{
	if (_state == m_state)
		return;

	m_state = _state;

	switch (_state)
	{
	case State::MoveLeft:
		m_pAnim->SetClip("Boss_Left");
		break;
	case State::MoveRight:
		m_pAnim->SetClip("Boss_Right");
		break;
	case State::MoveUp:
		m_pAnim->SetClip("Boss_Back");
		break;
	case State::MoveDown:
		m_pAnim->SetClip("Boss_Front");
		break;
	case State::Hit:
		m_pAnim->SetClip("Boss_Hit");
		break;
	case State::TrappedInBubble:
		m_pAnim->SetClip("Boss_Die1");
		break;
	case State::Die:
		m_pAnim->SetClip("Boss_Die2");
		break;
	}
}

void CBoss::Die()
{
	m_nextState = State::Die;
}

void CBoss::Attack()
{
	float deltaTime = CTimer::GetInst()->GetDeltaTime();
	m_attackDelayRemained += deltaTime;
	
	if (m_attackDelayRemained < m_attackDelay)	return;

	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(2, 3);
	m_attackDelay = distribution(engine);
	m_attackDelayRemained = 0.0f;

	std::uniform_int_distribution<int> distribution3(0, 1);
	int choice = distribution3(engine);

	CBoard* board = ((CInGameScene*)m_pScene)->GetBoard();

	//=========================================
	//  attack 1 처리 
	//=========================================
	if (choice == 0)
	{
		int startX, startY;
		Dir dir = Dir::Down;
		if (State::MoveLeft == m_state)
		{
			dir = Dir::Left;
			startX = m_cellXPos - 2;
			startY = m_cellYPos - 1;
		}
		else if (State::MoveRight == m_state)
		{
			dir = Dir::Right;
			startX = m_cellXPos + 4;
			startY = m_cellYPos - 1;
		}
		else if (State::MoveUp == m_state)
		{
			dir = Dir::Up;
			startX = m_cellXPos + 1;
			startY = m_cellYPos - 4;
		}
		else
		{
			dir = Dir::Down;
			startX = m_cellXPos + 1;
			startY = m_cellYPos + 2;
		}

		int stageFrameOffsetX = 20;
		int stageFrameOffsetY = 40;

		CBubble* bubble = new CBubble({
			(float)startX* BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)startY* BOARD_BLOCK_SIZE + stageFrameOffsetY,
			(float)startX* BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)startY* BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY
			},
			eInGameObjType::Balloon);
		bubble->SetOwner(this);
		bubble->SetSplashLength(1);
		D2D1_POINT_2U point = bubble->GetPoint();
		board->PutObj(point.x, point.y, bubble, eInGameObjType::Balloon);

		bubble->Move(dir);
	}
	//=========================================
	//  attack 2 처리 
	//=========================================
	else if (choice == 1)
	{
		int centerX = m_cellXPos + 1;
		int centerY = m_cellYPos - 1;
		int diameter;
		do {
			std::uniform_int_distribution<int> distribution2(5, 9);
			diameter = distribution2(engine);
		} while (diameter % 2 == 0);
		int radius = diameter / 2;

		for (int i = centerY - radius; i <= centerY + radius; i++)
		{
			for (int j = centerX - radius; j <= centerX + radius; j++)
			{
				if (centerY - radius + 1 <= i && i <= centerY + radius - 1
					&& centerX - radius + 1 <= j && j <= centerX + radius - 1)
					continue;
				board->PutSplash(j, i, "Explosion_center");
			}
		}
	}
}

State CBoss::RandomDir()
{
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(0, (int)Dir::None - 1);

	return (State)distribution(engine);
}