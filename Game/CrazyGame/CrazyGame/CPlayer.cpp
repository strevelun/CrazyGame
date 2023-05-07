#include "CPlayer.h"
#include "CBitmap.h"
#include "CScene.h"
#include "CInGameScene.h"
#include "CTimer.h"
#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CResourceManager.h"
#include "CBubble.h"
#include "CItem.h"
#include "CSceneManager.h"
#include "CVehicle.h"
#include "CBoss.h"

CPlayer::CPlayer(const D2D1_RECT_F& _rect, eInGameObjType _type) : CMoveObj(_rect)
{
	m_pAnim = new CAnimator;
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("bazzi_left");
	animClip->SetFrametimeLimit(0.1f);
	m_pAnim->AddClip("bazzi_left", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("bazzi_right");
	animClip->SetFrametimeLimit(0.1f);
	m_pAnim->AddClip("bazzi_right", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("bazzi_up");
	animClip->SetFrametimeLimit(0.1f);
	m_pAnim->AddClip("bazzi_up", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip("bazzi_down");
	animClip->SetFrametimeLimit(0.1f);
	m_pAnim->AddClip("bazzi_down", animClip);

	animClip = new CAnimationClip(*CResourceManager::GetInst()->GetAnimationClip("bazzi_die"));
	animClip->SetLoop(false);
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("bazzi_die", animClip);

	animClip = new CAnimationClip(*CResourceManager::GetInst()->GetAnimationClip("bazzi_ready"));
	animClip->SetLoop(false);
	animClip->SetFrametimeLimit(0.1f);
	m_pAnim->AddClip("bazzi_ready", animClip);
	m_pAnim->SetClip("bazzi_ready");

	m_xpos = _rect.left + (BOARD_BLOCK_SIZE / 2);
	m_ypos = _rect.bottom - (BOARD_BLOCK_SIZE / 2);

	m_speed = 210.0f;
	m_eType = _type;
}

CPlayer::~CPlayer()
{
	// bazzi_die�� ���� ����
	delete m_pAnim->GetClip("bazzi_die");
}


void CPlayer::Input()
{
	if (m_nextState == State::Die)
		return;

	switch (m_state)
	{
	case State::Idle:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_nextState = State::MoveLeft;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_nextState = State::MoveRight;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_nextState = State::MoveUp;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_nextState = State::MoveDown;
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bFire = true;
		}
		break;

	case State::MoveLeft:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_nextState = State::MoveLeft;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_nextState = State::MoveRight;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_nextState = State::MoveUp;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_nextState = State::MoveDown;
		}
		else
			m_nextState = State::Idle;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bFire = true;
		}

		break;
	case State::MoveRight:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_nextState = State::MoveLeft;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_nextState = State::MoveRight;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_nextState = State::MoveUp;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_nextState = State::MoveDown;
		}
		else
			m_nextState = State::Idle;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bFire = true;
		}
		break;
	case State::MoveUp:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_nextState = State::MoveLeft;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_nextState = State::MoveRight;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_nextState = State::MoveUp;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_nextState = State::MoveDown;
		}
		else
			m_nextState = State::Idle;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bFire = true;
		}
		break;

	case State::MoveDown:
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_nextState = State::MoveLeft;
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_nextState = State::MoveRight;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_nextState = State::MoveUp;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_nextState = State::MoveDown;
		}
		else
			m_nextState = State::Idle;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_bFire = true;
		}
		break;
	}
}

void CPlayer::Update()
{
	if (!m_vehicle && m_state != State::Idle)
		CObj::Update();

	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	if (m_bInvincible)
	{
		m_invincibleTime += deltaTime;
		if (m_invincibleTime >= 2.0f)
		{
			m_invincibleTime = 0.0f;
			m_bInvincible = false;
		}
	}

	D2D1_RECT_F rect = m_rect;
	rect.top += 20;
	//CObj::RectToPos(rect, m_cellXPos, m_cellYPos);

	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	m_cellXPos = (m_xpos - stageFrameOffsetX) / BOARD_BLOCK_SIZE;
	m_cellYPos = (m_ypos - stageFrameOffsetY) / BOARD_BLOCK_SIZE;




	CBoard* board = ((CInGameScene*)m_pScene)->m_board;

	int jumpHeight = BOARD_BLOCK_SIZE;

	CAnimationClip* clip = nullptr;

	// ���� != ���� ���� : PlayClip

	ChangeState(m_nextState);


	if (board->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Boss))
	{
		CBoss* boss = (CBoss*)board->GetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos);
		if (boss->GetState() == State::TrappedInBubble)
			boss->Die();
		else if (m_state != State::Die)
			Die();
	}

	switch (m_state)
	{
	case State::Ready:
		clip = m_pAnim->GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_nextState = State::Idle;
			m_pAnim->SetClip("bazzi_down");
			return;
		}
		break;
	case State::Idle:
		break;
	case State::MoveLeft:
	case State::MoveRight:
	case State::MoveUp:
	case State::MoveDown:
		MoveOnMoveObjBoard(this);
		MoveState();
		break;
	case State::Die:
		clip = m_pAnim->GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_isAlive = false;
			return;
		}
	break;
	}

	CItem* item = board->GetItem(m_cellXPos, m_cellYPos);

	// ž�� ������
	CItem* rideItem = nullptr;

	if (item)
	{
		switch (item->GetItemEnum())
		{
		case eItem::Gift_Skate:
			m_speed += 70;
			break;
		case eItem::Gift_Turtle:
			break;
		case eItem::Gift_UFO:
		{
			// ĳ���ʹ� �� �ڸ����� ���� �ִϸ��̼� ���� �� ž��

			if (m_vehicle)
				break;

			CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

			CLayer* layer = scene->FindLayer("Vehicle");

			if (layer)
			{
				m_rideRect = m_rect;
				m_vehicle = new CVehicle(m_rideRect, "UFO");
				layer->AddObj(m_vehicle);
				m_rect.top -= m_vehicle->GetRideHeight();
				m_rect.bottom -= m_vehicle->GetRideHeight();
				m_prevSpeed = m_speed;
				m_speed = m_vehicle->GetSpeed();
				m_bIsRiding = true;
			}

			//m_bIsJumping = true;
		}
		break;
		case eItem::Gift_Boom:
			m_splashLength = 8;
			break;
		case eItem::Gift_Bubble:
			m_bubbleCarryLimit += 1;
			break;
		case eItem::Gift_Dart: // ���� �Ÿ� ������ ��Ʈ ��ô
			break;
		case eItem::Gift_Devil: // ���� �ð����� ����Ű �ݴ�� �۵���
			break;
		case eItem::Gift_Owl:
			break;
		case eItem::Gift_Potion:
			m_splashLength++;
			break;
		case eItem::Gift_Shoes:
			m_bKickable = true;
			break;
		}
	}

	if (m_vehicle)
		m_vehicle->Update(m_rideRect);

	// �����̽��ٸ� �ѹ� ������ ������ Bubble�� ������
	if (m_bFire
		&& m_curBubblePlaced < m_bubbleCarryLimit
		&& (((CInGameScene*)m_pScene)->m_board->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon) == false))
	{

		CBubble* bubble = new CBubble({
			(float)m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY,
			(float)m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY
			},
			eInGameObjType::Balloon);
		bubble->SetPlayer(this);
		bubble->SetSplashLength(m_splashLength);
		D2D1_POINT_2U point = bubble->GetPoint();
		if (((CInGameScene*)m_pScene)->m_board->PutObj(point.x, point.y, bubble, eInGameObjType::Balloon))
			m_curBubblePlaced++;
		else
			delete bubble;
	}

	m_bFire = false;

}

// ���� ���¸� ����� ~~
void CPlayer::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(0.9f, 0.8f, D2D1::Point2F(m_rect.left - 80, m_rect.bottom )));
	m_pAnim->Render(_pRenderTarget, m_rect);
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	if (m_vehicle)
		m_vehicle->Render(_pRenderTarget);
}

void CPlayer::Die() 
{
	if (m_bInvincible)
		return;

	m_nextState = State::Die;
	//MessageBox(NULL, L"���", L"���", MB_OK);
	m_pAnim->SetClip("bazzi_die");
}

void CPlayer::MoveState()
{
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	CBoard* board = ((CInGameScene*)m_pScene)->m_board;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	int x = 0, y = 0;

	int cellUpYPos = (m_ypos  + 5- stageFrameOffsetY - BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE;
	int cellDownYPos = (m_ypos - 5- stageFrameOffsetY + BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE;
	int cellLeftXPos = (m_xpos + 5- stageFrameOffsetX - BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE;
	int cellRightXPos = (m_xpos - 5 - stageFrameOffsetX + BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE; 

	
	// �̲����� ó�� �ڵ� - ���� ����
	if (m_state == State::MoveLeft)
	{
		int limit = m_cellXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetX;
		// ����
		if (!board->IsMovable(m_cellXPos - 1, cellDownYPos, m_vehicle)) // �߳��� �������� x-1�� ����� ���� ���
		{
			if (limit < m_xpos)
				x = -1;
			else 
				if (cellDownYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetY > m_ypos
					&& board->IsMovable(m_cellXPos - 1, cellDownYPos - 1, m_vehicle))
					y = -1;
		}
		// �Ʒ���
		else if (!board->IsMovable(m_cellXPos - 1, cellUpYPos, m_vehicle))
		{
			if (limit < m_xpos)
				x = -1;
			else
				if (cellUpYPos * BOARD_BLOCK_SIZE + ((BOARD_BLOCK_SIZE / 10) * 9) + stageFrameOffsetY < m_ypos
					&& board->IsMovable(m_cellXPos - 1, cellUpYPos + 1, m_vehicle))
					y = 1;
		}
		else
		{
			x = -1;
		}

		if (m_bKickable)
		{
			if (board->IsGameObjType(m_cellXPos - 1, m_cellYPos, eInGameObjType::Balloon))
			{
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
				CObj* pObj = pLayer->FindObj(m_cellXPos - 1, m_cellYPos);
				if (pObj)
				{
					((CBubble*)pObj)->Move(Dir::Left);
				}
			}
		}

	}
	else if (m_state == State::MoveRight)
	{
		int limit = m_cellXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetX;
		// ����
		if (!board->IsMovable(m_cellXPos + 1, cellDownYPos, m_vehicle)) // �߳��� �������� x-1�� ����� ���� ���
		{
			if (limit > m_xpos)
				x = 1;
			else
				if (cellDownYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetY > m_ypos
					&& board->IsMovable(m_cellXPos + 1, cellDownYPos - 1, m_vehicle))
					y = -1;
		}
		// �Ʒ���
		else if (!board->IsMovable(m_cellXPos + 1, cellUpYPos, m_vehicle))
		{
			if (limit > m_xpos)
				x = 1;
			else
				if (cellUpYPos * BOARD_BLOCK_SIZE + ((BOARD_BLOCK_SIZE / 10) * 9) + stageFrameOffsetY < m_ypos
					&& board->IsMovable(m_cellXPos + 1, cellUpYPos + 1, m_vehicle))
					y = 1;
		}
		else
		{
			x = 1;
		}

		if (m_bKickable)
		{
			if (board->IsGameObjType(m_cellXPos + 1, m_cellYPos, eInGameObjType::Balloon))
			{
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
				CObj* pObj = pLayer->FindObj(m_cellXPos + 1, m_cellYPos);
				if (pObj)
				{
					((CBubble*)pObj)->Move(Dir::Right);
				}
			}
		}
	}
	else if (m_state == State::MoveUp)
	{
		int limit = m_cellYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetY;
		// ��������
		if (!board->IsMovable(cellRightXPos, m_cellYPos - 1, m_vehicle))
		{
			if (limit < m_ypos)
				y = -1;
			else
				if (cellRightXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetX > m_xpos
					&& board->IsMovable(cellRightXPos-1, m_cellYPos-1, m_vehicle)) // �̲������� ������ ĭ�� �� �� �ִ� ������
					x = -1;
		}
		// ����������
		else if (!board->IsMovable(cellLeftXPos, m_cellYPos-1, m_vehicle))
		{
			if (limit < m_ypos)
				y = -1;
			else
				if (cellLeftXPos * BOARD_BLOCK_SIZE + ((BOARD_BLOCK_SIZE / 10) * 9) + stageFrameOffsetX < m_xpos
					&& board->IsMovable(cellLeftXPos+1, m_cellYPos-1, m_vehicle))
					x = 1;
		}
		else
			y = -1;

		if (m_bKickable)
		{
			if (board->IsGameObjType(m_cellXPos, m_cellYPos -1, eInGameObjType::Balloon))
			{
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
				CObj* pObj = pLayer->FindObj(m_cellXPos, m_cellYPos-1);
				if (pObj)
				{
					((CBubble*)pObj)->Move(Dir::Up);
				}
			}
		}
	}
	else if (m_state == State::MoveDown)
	{
		int limit = m_cellYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetY;

		if (!board->IsMovable(cellRightXPos, m_cellYPos + 1, m_vehicle))
		{
			if (limit > m_ypos)
				y = 1;
			else
				if (cellRightXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetX > m_xpos
					&& board->IsMovable(cellRightXPos-1, m_cellYPos+1, m_vehicle))
					x = -1;
		}
		else if (!board->IsMovable(cellLeftXPos, m_cellYPos + 1, m_vehicle))
		{
			if (limit > m_ypos)
				y = 1;
			else
				if (cellLeftXPos * BOARD_BLOCK_SIZE + ((BOARD_BLOCK_SIZE / 10) * 9) + stageFrameOffsetX < m_xpos
					&& board->IsMovable(cellLeftXPos+1, m_cellYPos+1, m_vehicle))
					x = 1;
		}
		else
			y = 1;

		if (m_bKickable)
		{
			if (board->IsGameObjType(m_cellXPos, m_cellYPos + 1, eInGameObjType::Balloon))
			{
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
				CObj* pObj = pLayer->FindObj(m_cellXPos, m_cellYPos+1);
				if (pObj)
				{
					((CBubble*)pObj)->Move(Dir::Down);
				}
			}
		}
	}

	m_xpos += m_speed * deltaTime * x;
	m_ypos += m_speed * deltaTime * y;

	m_rect.left += m_speed * deltaTime * x;
	m_rect.right += m_speed * deltaTime * x;
	m_rect.top += m_speed * deltaTime * y;
	m_rect.bottom += m_speed * deltaTime * y;

	if (m_vehicle)
	{
		m_rideRect.left += m_speed * deltaTime * x;
		m_rideRect.right += m_speed * deltaTime * x;
		m_rideRect.top += m_speed * deltaTime * y;
		m_rideRect.bottom += m_speed * deltaTime * y;
	}
}

void CPlayer::ChangeState(State _state)
{
	if (_state == m_state)
		return;

	m_state = _state;
	//m_nextState = State::None;

	switch (_state)
	{
	case State::Idle:
		m_pAnim->GetCurClip()->SetCurFrameIdx(0);
		break;
	case State::MoveLeft:
		m_pAnim->SetClip("bazzi_left");
		if (m_vehicle)
			m_vehicle->SetDir(Dir::Left);
		break;
	case State::MoveRight:
		m_pAnim->SetClip("bazzi_right");
		if (m_vehicle)
			m_vehicle->SetDir(Dir::Right);
		break;
	case State::MoveUp:
		m_pAnim->SetClip("bazzi_up");
		if (m_vehicle)
			m_vehicle->SetDir(Dir::Up);
		break;
	case State::MoveDown:
		m_pAnim->SetClip("bazzi_down");
		if (m_vehicle)
			m_vehicle->SetDir(Dir::Down);
		break;
	}
}

std::string CPlayer::GetStrDir(Dir _dir)
{
	std::string strDir = "";
	switch (_dir)
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

	return strDir;
}

// ��Ȱ�ϰų� ���� �Ŀ��� �����ð� ���� ����
void CPlayer::GetOffVehicle()
{
	m_bInvincible = true;
	m_bIsRiding = false;
	m_speed = m_prevSpeed;

	m_rect.top += m_vehicle->GetRideHeight();
	m_rect.bottom += m_vehicle->GetRideHeight();
	m_vehicle->SetAlive(false);
	m_vehicle = nullptr;
}