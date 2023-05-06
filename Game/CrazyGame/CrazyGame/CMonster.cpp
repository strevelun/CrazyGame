#include "CMonster.h"
#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CResourceManager.h"
#include "CBoard.h"
#include "CInGameScene.h"
#include "CSceneManager.h"
#include "CTimer.h"

#include <random>

// 29 31
CMonster::CMonster(const D2D1_RECT_F& _rect, eInGameObjType _type) : CMoveObj(_rect)
{
	m_pAnim = new CAnimator;
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("Monster01_Front");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Monster01_Front", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Monster01_Back");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Monster01_Back", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Monster01_Left");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Monster01_Left", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("Monster01_Right");
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("Monster01_Right", animClip);
	m_pAnim->SetClip("Monster01_Front");


	m_xpos = _rect.left + (BOARD_BLOCK_SIZE / 2);
	m_ypos = _rect.bottom - (BOARD_BLOCK_SIZE / 2);

	m_state = State::MoveDown;

	m_speed = 45.0f;
	m_eType = _type;
}

CMonster::~CMonster()
{
}

void CMonster::MoveState()
{
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();
	float deltaTime = CTimer::GetInst()->GetDeltaTime();


	int x = 0, y = 0;

	if (m_state == State::MoveLeft)
	{
		if (board->IsMovable(m_cellXPos - 1, m_cellYPos) == false)
		{
			m_nextState = RandomDir();
			return;
		} 
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		board->SetObjTypeInMoveObjBoard(m_cellXPos - 1, m_cellYPos, this);

		x = -1;

	}
	else if (m_state == State::MoveRight)
	{
		if (board->IsMovable(m_cellXPos + 1, m_cellYPos) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		board->SetObjTypeInMoveObjBoard(m_cellXPos + 1, m_cellYPos, this);

		x = 1;
	}
	else if (m_state == State::MoveUp)
	{
		if (board->IsMovable(m_cellXPos, m_cellYPos - 1) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos-1, this);

		y = -1;
	}
	else if (m_state == State::MoveDown)
	{
		if (board->IsMovable(m_cellXPos, m_cellYPos + 1) == false)
		{
			m_nextState = RandomDir();
			return;
		}
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos+1, this);

		y = 1;
	}


	m_xpos += m_speed * deltaTime * x;
	m_ypos += m_speed * deltaTime * y;

	m_rect.left += m_speed * deltaTime * x;
	m_rect.right += m_speed * deltaTime * x;
	m_rect.top += m_speed * deltaTime * y;
	m_rect.bottom += m_speed * deltaTime * y;
}

void CMonster::ChangeState(State _state)
{
	if (_state == m_state)
		return;

	m_state = _state;

	switch (_state)
	{
	case State::MoveLeft:
		m_pAnim->SetClip("Monster01_Left");
		break;
	case State::MoveRight:
		m_pAnim->SetClip("Monster01_Right");
		break;
	case State::MoveUp:
		m_pAnim->SetClip("Monster01_Back");
		break;
	case State::MoveDown:
		m_pAnim->SetClip("Monster01_Front");
		break;
	}
}

State CMonster::RandomDir()
{
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(0, (int)Dir::None - 1);

	State state;
	Dir dir = (Dir)distribution(engine);


	if (dir == Dir::Left)
		state = State::MoveLeft;
	else if (dir == Dir::Right)
		state = State::MoveRight;
	else if (dir == Dir::Up)
		state = State::MoveUp;
	else if (dir == Dir::Down)
		state = State::MoveDown;
	return state;
}

void CMonster::Update()
{
	CObj::Update();

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	m_cellXPos = (m_xpos - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = (m_ypos - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	ChangeState(m_nextState);

	switch (m_state)
	{
	case State::Ready:
		m_nextState = State::MoveUp;

		break;
	case State::MoveLeft:
	case State::MoveRight:
	case State::MoveUp:
	case State::MoveDown:
		MoveState();
		break;
	case State::Die:

		m_isAlive = false;
		break;
	}
}

void CMonster::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_pAnim->Render(_pRenderTarget, m_rect);
}
