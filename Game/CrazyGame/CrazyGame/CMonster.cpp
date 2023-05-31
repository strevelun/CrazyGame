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
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(L"Monster01_Front");
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"Monster01_Front", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"Monster01_Back");
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"Monster01_Back", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"Monster01_Left");
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"Monster01_Left", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"Monster01_Right");
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"Monster01_Right", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"Monster01_Die");
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"Monster01_Die", animClip);

	m_anim.SetClip(L"Monster01_Front");


	m_xpos = _rect.left + 15;
	m_ypos = _rect.bottom - 15;

	m_state = State::Ready;

	m_speed = 145.0f;
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
	int width = (int)(m_rect.right - m_rect.left);
	int height = (int)(m_rect.bottom - m_rect.top);

	int x = 0, y = 0;

	if (m_state == State::MoveLeft)
	{
		x = -1;

		if (board->IsMovable(m_cellXPos - 1, m_cellYPos) == false)
		{
			if (BOARD_BLOCK_SIZE * m_cellXPos + stageFrameOffsetX < m_rect.left)
			{
				m_xpos += m_speed * deltaTime * x;
				m_rect.left += m_speed * deltaTime * x;
				m_rect.right += m_speed * deltaTime * x;
			}
			else
			{
				m_nextState = RandomDir();
				m_xpos = BOARD_BLOCK_SIZE * (float)m_cellXPos + stageFrameOffsetX + 15;
				m_rect.left = BOARD_BLOCK_SIZE * (float)m_cellXPos + stageFrameOffsetX;
				m_rect.right = m_rect.left + width;
			}
			return;
		} 


	}
	else if (m_state == State::MoveRight)
	{

		x = 1;
		if (board->IsMovable(m_cellXPos + 1, m_cellYPos) == false)
		{
			if (BOARD_BLOCK_SIZE * (m_cellXPos + 1)+ stageFrameOffsetX > m_rect.right)
			{
				m_xpos += m_speed * deltaTime * x;
				m_rect.left += m_speed * deltaTime * x;
				m_rect.right += m_speed * deltaTime * x;
			}
			else
			{
				m_nextState = RandomDir();
				m_xpos = BOARD_BLOCK_SIZE * (float)(m_cellXPos + 1) + stageFrameOffsetX - 15;
				m_rect.right = BOARD_BLOCK_SIZE * (float)(m_cellXPos + 1) + stageFrameOffsetX;
				m_rect.left = m_rect.right - width;
			}
			return;
		}
	}
	else if (m_state == State::MoveUp)
	{
		y = -1;
		if (board->IsMovable(m_cellXPos, m_cellYPos - 1) == false)
		{
			if (BOARD_BLOCK_SIZE * m_cellYPos + stageFrameOffsetY < m_rect.top)
			{
				m_ypos += m_speed * deltaTime * y;
				m_rect.top += m_speed * deltaTime * y;
				m_rect.bottom += m_speed * deltaTime * y;
			}
			else
			{
				m_nextState = RandomDir();
				m_ypos = BOARD_BLOCK_SIZE * (float)m_cellYPos + stageFrameOffsetY + 15;
				m_rect.top = BOARD_BLOCK_SIZE * (float)m_cellYPos + stageFrameOffsetY;
				m_rect.bottom = m_rect.top + height;
			}
			return;
		}

	}
	else if (m_state == State::MoveDown)
	{
		y = 1;
		if (board->IsMovable(m_cellXPos, m_cellYPos + 1) == false)
		{
			if (BOARD_BLOCK_SIZE * (m_cellYPos + 1) + stageFrameOffsetY > m_rect.bottom)
			{
				m_ypos += m_speed * deltaTime * y;
				m_rect.top += m_speed * deltaTime * y;
				m_rect.bottom += m_speed * deltaTime * y;
			}
			else
			{
				m_nextState = RandomDir();
				m_ypos = BOARD_BLOCK_SIZE * (float)(m_cellYPos + 1) + stageFrameOffsetY - 15;
				m_rect.bottom = BOARD_BLOCK_SIZE * (float)(m_cellYPos + 1) + stageFrameOffsetY;
				m_rect.top = m_rect.bottom - height;
			}
			return;
		}
	}


	board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);

	m_xpos += m_speed * deltaTime * x;
	m_ypos += m_speed * deltaTime * y;

	m_rect.left += m_speed * deltaTime * x;
	m_rect.right += m_speed * deltaTime * x;
	m_rect.top += m_speed * deltaTime * y;
	m_rect.bottom += m_speed * deltaTime * y;

	m_cellXPos = (m_xpos - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = (m_ypos - stageFrameOffsetY) / BOARD_BLOCK_SIZE;

	board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, this);
}

void CMonster::ChangeState(State _state)
{
	if (_state == m_state)
		return;

	m_state = _state;

	switch (_state)
	{
	case State::MoveLeft:
		m_anim.SetClip(L"Monster01_Left");
		break;
	case State::MoveRight:
		m_anim.SetClip(L"Monster01_Right");
		break;
	case State::MoveUp:
		m_anim.SetClip(L"Monster01_Back");
		break;
	case State::MoveDown:
		m_anim.SetClip(L"Monster01_Front");
		break;
	case State::Die:
		m_anim.SetClip(L"Monster01_Die");
	}
}

State CMonster::RandomDir()
{
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(0, (int)eDir::None - 1);

	return (State)distribution(engine);
}

void CMonster::Die()
{
	m_nextState = State::Die;
}

void CMonster::Update()
{
	CGameObj::Update();

	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->GetBoard();

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	CAnimationClip* clip = nullptr;

	ChangeState(m_nextState);

	switch (m_state)
	{
	case State::Ready:
		m_passiveTime += CTimer::GetInst()->GetDeltaTime();
		if(m_passiveTime >= m_passiveTimeLimit)
			m_nextState = State::MoveDown;

		break;
	case State::MoveLeft:
	case State::MoveRight:
	case State::MoveUp:
	case State::MoveDown:
		MoveState();
		break;
	case State::Die:
		board->SetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos, nullptr);
		clip = m_anim.GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_isAlive = false;
			return;
		}
	}
}

void CMonster::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_anim.Render(_pRenderTarget, m_rect); 
	_pRenderTarget->DrawRectangle(
		D2D1::RectF(m_cellXPos * 40 + 20, m_cellYPos * 40 + 40,
			m_cellXPos * 40 + 20 + 40, m_cellYPos * 40 + 40 + 40), CCore::GetInst()->GetBrush());
}
