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
#include "Stage.h"
#include "StageManager.h"
#include "CUI.h"
#include "CBlock.h"

CPlayer::CPlayer(const D2D1_RECT_F& _rect, eInGameObjType _type) : CMoveObj(_rect)
{
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(L"bazzi_left");
	animClip->SetFrametimeLimit(0.1f);
	m_anim.AddClip(L"bazzi_left", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"bazzi_right");
	animClip->SetFrametimeLimit(0.1f);
	m_anim.AddClip(L"bazzi_right", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"bazzi_up");
	animClip->SetFrametimeLimit(0.1f);
	m_anim.AddClip(L"bazzi_up", animClip);
	animClip = CResourceManager::GetInst()->GetAnimationClip(L"bazzi_down");
	animClip->SetFrametimeLimit(0.1f);
	m_anim.AddClip(L"bazzi_down", animClip);
	
	animClip = new CAnimationClip(*CResourceManager::GetInst()->GetAnimationClip(L"bazzi_die"));
	animClip->SetLoop(false);
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"bazzi_die", animClip);

	animClip = new CAnimationClip(*CResourceManager::GetInst()->GetAnimationClip(L"bazzi_trap"));
	animClip->SetLoop(false);
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(L"bazzi_trap", animClip);

	animClip = new CAnimationClip(*CResourceManager::GetInst()->GetAnimationClip(L"bazzi_ready"));
	animClip->SetLoop(false);
	animClip->SetFrametimeLimit(3.0f / 18); // 씬 ready시간 3초 / 프레임수
	m_anim.AddClip(L"bazzi_ready", animClip);
	m_anim.SetClip(L"bazzi_ready");

	m_xpos = _rect.left + (BOARD_BLOCK_SIZE / 2);
	m_ypos = _rect.bottom - (BOARD_BLOCK_SIZE / 2);

	m_speed = 210.0f;
	m_eType = _type;
	m_size.width = _rect.right - _rect.left;
	m_size.height = _rect.bottom - _rect.top;

	m_smInst = StageManager::GetInst();
	m_smInst->GetStage()->AddMoveObjCnt(MoveObjType::Player);

	m_pShadow = CResourceManager::GetInst()->GetBitmap(L"ShadowCharacter.png")->GetBitmap();
}

CPlayer::~CPlayer()
{
	// bazzi_die만 따로 해제
	delete m_anim.GetClip(L"bazzi_die");
}


void CPlayer::Input()
{
	if (m_nextState == State::Die) return;
	if (m_bIsJumping == true) return;
	if (m_bIsGettingOff == true) return;

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
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_attackDelay >= 0.2f)
		{
			m_bFire = true;
		}
		break;

	case State::MoveLeft:
		m_eMoveDir = eDir::Left;
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

		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_attackDelay >= 0.2f)
		{
			m_bFire = true;
		}

		break;
	case State::MoveRight:
		m_eMoveDir = eDir::Right;
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

		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_attackDelay >= 0.2f)
		{
			m_bFire = true;
		}
		break;
	case State::MoveUp:
		m_eMoveDir = eDir::Up;
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

		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_attackDelay >= 0.2f)
		{
			m_bFire = true;
		}
		break;

	case State::MoveDown:
		m_eMoveDir = eDir::Down;
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

		if (GetAsyncKeyState(VK_SPACE) & 0x8000 && m_attackDelay >= 0.2f)
		{
			m_bFire = true;
		}
		
		break;
	}

}

void CPlayer::Update()
{
	Input();

	if (!m_vehicle && m_state != State::Idle)
		CGameObj::Update();


	if (m_smInst->GetStage()->GetStageState() == eStageState::End)
	{
		m_state = State::Idle;
		return;
	}

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



	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board;

	int jumpHeight = BOARD_BLOCK_SIZE;

	CAnimationClip* clip = nullptr;

	// 현재 != 이전 상태 : PlayClip

	ChangeState(m_nextState);


	if (board->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Boss))
	{
		CBoss* boss = (CBoss*)board->GetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos);
		if (boss->GetState() == State::TrappedInBubble)
			boss->Die();
		else if (m_state != State::Die)
		{
			if(m_vehicle == nullptr)
				Die();
		}
	}

	if (m_bIsJumping)
	{
		if (m_rect.bottom >= m_vehicle->GetRect().bottom - 10)
			m_bIsJumping = false;

		m_rect.top += 100 * deltaTime;
		m_rect.bottom += 100 * deltaTime;

		return;
	}

	if (m_bIsGettingOff)
	{
		if (m_rect.bottom >= m_ypos + (BOARD_BLOCK_SIZE / 2))
			m_bIsGettingOff = false;

		m_rect.top += 100 * deltaTime;
		m_rect.bottom += 100 * deltaTime;		
		return;
	}

	switch (m_state)
	{
	case State::Ready:
		if (m_smInst->GetStage()->GetStageState() == eStageState::Play)
		{
			m_nextState = State::Idle;
			m_anim.SetClip(L"bazzi_down");
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
	case State::Hit:
		break;
	case State::TrappedInBubble:
		clip = m_anim.GetCurClip();
		if (!clip) return;
		// 다트 아이템 쓰면 SetClip(live)하고 Idle상태로.

		if (clip->IsCurClipEnd())
		{
			Die();
			return;
		}
		break;
	case State::Die:
		clip = m_anim.GetCurClip();
		if (!clip) return;

		if (clip->IsCurClipEnd())
		{
			m_isAlive = false;
			m_smInst->GetStage()->SubMoveObjCnt(MoveObjType::Player);
			return;
		}
	break;
	}

	CItem* item = board->GetItem(m_cellXPos, m_cellYPos);

	// 탑승 아이템
	CItem* rideItem = nullptr;

	if (item)
	{
		//item->Benfit(this);

		switch (item->GetItemEnum())
		{
		case eItem::Gift_Skate:
			m_speed += 70;
			break;
		//case eItem::Gift_Turtle:
		//	break;
		case eItem::Gift_UFO:
		{
			// 캐릭터는 그 자리에서 점프 애니메이션 취한 후 탑승

			if (m_vehicle)
				break;

			CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

			CLayer* layer = scene->FindLayer(L"Vehicle");

			if (layer)
			{
				m_rideRect = { (float)m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX, (float)m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY, (float)m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX, (float)m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY };

				m_rideRect.bottom -= BOARD_BLOCK_SIZE / 3;
				m_vehicle = new CVehicle(m_rideRect, L"UFO");
				D2D1_SIZE_U size = m_vehicle->GetSize();
				m_rideRect.top = m_rideRect.bottom - size.height;
				m_rideRect.left -= (size.width - BOARD_BLOCK_SIZE )/ 2;
				m_rideRect.right -= (size.width - BOARD_BLOCK_SIZE) / 2;
				m_vehicle->SetRect(m_rideRect);
				m_vehicle->SetDir(m_eMoveDir);
				//layer->AddObj(m_vehicle);

				m_xpos = (float)m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX + (BOARD_BLOCK_SIZE / 2);
				m_ypos = (float)m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY + (BOARD_BLOCK_SIZE / 2);
				m_rect.left = m_xpos - (m_size.width / 3) - 3;
				m_rect.right = m_xpos + (m_size.width / 3) - 3;
				m_rect.bottom = m_vehicle->GetRect().top;
				m_rect.top = m_rect.bottom - m_size.height;
				m_prevSpeed = m_speed;
				m_speed = m_vehicle->GetSpeed();
				m_bIsRiding = true;
				m_bIsJumping = true;
			}

		}
		break;
		case eItem::Gift_Boom:
			m_splashLength = 8;
			break;
		case eItem::Gift_Bubble:
			m_bubbleCarryLimit += 1;
			break;
		//case eItem::Gift_Dart:
		//	break;
		//case eItem::Gift_Devil: // 일정 시간동안 방향키 반대로 작동함
		//	break;
		//case eItem::Gift_Owl:
		//	break;
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


	if (m_bFire )
	{
		m_attackDelay = 0;
		m_spaceCount++;
		if (!m_spacePressed)
		{
			m_spacePressed = true;
		}
	}


	if (m_bFire
		&& m_curBubblePlaced < m_bubbleCarryLimit
		&& (((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon) == false))
	{

 		CBubble* bubble = new CBubble({
			(float)m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY,
			(float)m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX,
			(float)m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY
			},
			eInGameObjType::Balloon);
 		bubble->SetOwner(this);
		//bubble->SetScene(m_pScene);
		bubble->SetSplashLength(m_splashLength);
		D2D1_POINT_2U point = bubble->GetPoint();
		if (((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->PutObj(point.x, point.y, bubble, eInGameObjType::Balloon))
			m_curBubblePlaced++;
		else
			delete bubble;
	}	

	if (m_spacePressed && m_doubleSpaceDeltaTime <= 0.5f && m_doubleSpaceDeltaTime >= 0.2f)
	{
		if (m_spaceCount >= 2)
		{
			m_spaceCount = 0;
			m_doubleSpaceDeltaTime = 0.0f;
			m_spacePressed = false;
			CGameObj* obj = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->FindLayer(L"Block")->FindGameObj(m_cellXPos, m_cellYPos, eInGameObjType::Balloon);
			if (obj != nullptr)
			{
				((CBubble*)obj)->BounceMove(m_eMoveDir);
			}

		}
	}
	else if (m_doubleSpaceDeltaTime >= 0.5f)
	{
		m_spaceCount = 0;
		m_doubleSpaceDeltaTime = 0.0f;
		m_spacePressed = false;
	}

	if (m_spacePressed)
	{
		m_doubleSpaceDeltaTime += deltaTime;
	}
	m_attackDelay += deltaTime;

	m_bFire = false;

	D2D1_RECT_F rectCheck = m_rect;
	int x = 0, y = 0;
	if (m_eMoveDir == eDir::Left)
		x = -1;
	else if (m_eMoveDir == eDir::Right)
		x = 1;
	else if (m_eMoveDir == eDir::Up)
		y = -1;
	else if (m_eMoveDir == eDir::Down)
		y = 1;

	CBlock* obj = (CBlock*)(CSceneManager::GetInst()->GetCurScene()->FindLayer(L"Block")->FindGameObj(m_cellXPos + x, m_cellYPos+ y, eInGameObjType::Block_Destructible));
	if (obj)
	{
		if (obj->GetBitmapIdx() == 1 || obj->GetBitmapIdx() == 4)
		{
			bool canMove = false;
			if (m_state == State::MoveLeft && obj->GetRect().right >= (int)m_rect.left)
				canMove = true;
			else if (m_state == State::MoveRight && obj->GetRect().left <= (int)m_rect.right)
				canMove = true;
			else if (m_state == State::MoveUp && obj->GetRect().bottom >= (int)m_rect.top)
				canMove = true;
			else if (m_state == State::MoveDown && obj->GetRect().top <= (int)m_rect.bottom)
				canMove = true;

			if (canMove)
			{
				obj->Move(m_eMoveDir);
			}
			else
				obj->Move(eDir::None);
		}
	}



}

void CPlayer::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(m_pShadow, { m_rect.left, m_ypos+10, m_rect.left + 40, m_ypos+20 });
	
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(0.9f, 0.8f, D2D1::Point2F(m_rect.left - 80, m_rect.bottom )));
	m_anim.Render(_pRenderTarget, m_rect);
	_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	if (m_vehicle)
		m_vehicle->Render(_pRenderTarget);
}

void CPlayer::Die() 
{
	if (m_bInvincible)
		return;
	m_nextState = State::Die;
}

void CPlayer::Hit()
{
	if (m_bInvincible || m_state == State::TrappedInBubble) // 물줄기에 
		return;
	m_nextState = State::TrappedInBubble;
}

void CPlayer::MoveState()
{
	//D2D_VECTOR_2F 
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;
	CBoard* board = ((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	int x = 0, y = 0;

	// 플레이어의 cellPos
	int cellUpYPos = (m_ypos  + 5- stageFrameOffsetY - BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE;  
	int cellDownYPos = (m_ypos - 5- stageFrameOffsetY + BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE;
	int cellLeftXPos = (m_xpos + 5- stageFrameOffsetX - BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE;
	int cellRightXPos = (m_xpos - 5 - stageFrameOffsetX + BOARD_BLOCK_SIZE / 2) / BOARD_BLOCK_SIZE; 

	
	// 미끄러짐 처리 코드 - 추후 수정
	if (m_state == State::MoveLeft)
	{
		int limit = m_cellXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetX;
		// 위로
		if (!board->IsMovable(m_cellXPos - 1, cellDownYPos, m_vehicle)) // 발끝을 기준으로 x-1에 블록이 있을 경우
		{
			if (limit < (int)m_xpos)
				x = -1;
			else 
				if (cellDownYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetY > m_ypos
					&& board->IsMovable(m_cellXPos - 1, cellDownYPos - 1, m_vehicle))
					y = -1;
		}
		// 아래로
		else if (!board->IsMovable(m_cellXPos - 1, cellUpYPos, m_vehicle))
		{
			if (limit < (int)m_xpos)
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
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer(L"Block");
				CObj* pObj = pLayer->FindGameObj(m_cellXPos - 1, m_cellYPos, eInGameObjType::Balloon);
				if (pObj)
				{
					((CBubble*)pObj)->Move(eDir::Left);
				}
			}
		}

	}
	else if (m_state == State::MoveRight)
	{
		int limit = m_cellXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetX;
		// 위로
		if (!board->IsMovable(m_cellXPos + 1, cellDownYPos, m_vehicle)) // 발끝을 기준으로 x-1에 블록이 있을 경우
		{
			if (limit > (int)m_xpos)
				x = 1;
			else
				if (cellDownYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetY > m_ypos
					&& board->IsMovable(m_cellXPos + 1, cellDownYPos - 1, m_vehicle))
					y = -1;
		}
		// 아래로
		else if (!board->IsMovable(m_cellXPos + 1, cellUpYPos, m_vehicle))
		{
			if (limit > (int)m_xpos)
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
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer(L"Block");
				CObj* pObj = pLayer->FindGameObj(m_cellXPos + 1, m_cellYPos, eInGameObjType::Balloon);
				if (pObj)
				{
					((CBubble*)pObj)->Move(eDir::Right);
				}
			}
		}
	}
	else if (m_state == State::MoveUp)
	{
		int limit = m_cellYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetY;
		// 왼쪽
		if (!board->IsMovable(cellRightXPos, m_cellYPos - 1, m_vehicle))
		{
			if (limit < (int)m_ypos)
				y = -1;
			else
				if (cellRightXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetX > m_xpos
					&& board->IsMovable(cellRightXPos-1, m_cellYPos-1, m_vehicle)) // 미끄러져서 도착한 칸이 갈 수 있는 곳인지
					x = -1;
		}
		// 위로 올라갈때 플레이어 윗줄의 오른쪽을 갈 수 없다면
		else if (!board->IsMovable(cellLeftXPos, m_cellYPos-1, m_vehicle))
		{
			if (limit < (int)m_ypos)
				y = -1;
			else // 플레이어의 y좌표가 아직 현재 cell 위치의 절반을 넘었다면
				// 플레이어의 왼쪽옆구리 기준 cellXPos + 타일의 9/10 && 플레이어의 왼쪽 위를 갈 수 있
				if (cellLeftXPos * BOARD_BLOCK_SIZE + ((BOARD_BLOCK_SIZE / 10) * 9) + stageFrameOffsetX < m_xpos
					&& board->IsMovable(cellLeftXPos + 1, m_cellYPos - 1, m_vehicle))
				{
					x = 1; // 오른쪽으로 미끄러짐
					//if(cellLeftXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetY < (int)(m_speed * deltaTime * x))
				}
		}
		else // 당장 눈 앞에 아무것도 없을 경우
			y = -1;

		if (m_bKickable)
		{
			if (board->IsGameObjType(m_cellXPos, m_cellYPos -1, eInGameObjType::Balloon))
			{
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer(L"Block");
				CObj* pObj = pLayer->FindGameObj(m_cellXPos, m_cellYPos-1, eInGameObjType::Balloon);
				if (pObj)
				{
					((CBubble*)pObj)->Move(eDir::Up);
				}
			}
		}
	}
	else if (m_state == State::MoveDown)
	{
		int limit = m_cellYPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 2) + stageFrameOffsetY;

		if (!board->IsMovable(cellRightXPos, m_cellYPos + 1, m_vehicle))
		{
			if (limit > (int)m_ypos)
				y = 1;
			else
				if (cellRightXPos * BOARD_BLOCK_SIZE + (BOARD_BLOCK_SIZE / 10) + stageFrameOffsetX > m_xpos
					&& board->IsMovable(cellRightXPos-1, m_cellYPos+1, m_vehicle))
					x = -1;
		}
		else if (!board->IsMovable(cellLeftXPos, m_cellYPos + 1, m_vehicle))
		{
			if (limit > (int)m_ypos)
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
				CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer(L"Block");
				CObj* pObj = pLayer->FindGameObj(m_cellXPos, m_cellYPos+1, eInGameObjType::Balloon);
				if (pObj)
				{
					((CBubble*)pObj)->Move(eDir::Down);
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
		m_anim.GetCurClip()->SetCurFrameIdx(0);
		break;
	case State::MoveLeft:
		m_anim.SetClip(L"bazzi_left");
		if (m_vehicle)
			m_vehicle->SetDir(eDir::Left);
		break;
	case State::MoveRight:
		m_anim.SetClip(L"bazzi_right");
		if (m_vehicle)
			m_vehicle->SetDir(eDir::Right);
		break;
	case State::MoveUp:
		m_anim.SetClip(L"bazzi_up");
		if (m_vehicle)
			m_vehicle->SetDir(eDir::Up);
		break;
	case State::MoveDown:
		m_anim.SetClip(L"bazzi_down");
		if (m_vehicle)
			m_vehicle->SetDir(eDir::Down);
		break;
	case State::TrappedInBubble:
		m_anim.SetClip(L"bazzi_trap");
		break;
	case State::Die:
		m_anim.SetClip(L"bazzi_die");

		break;
	}
}

std::wstring CPlayer::GetStrDir(eDir _dir)
{
	std::wstring strDir = L"";
	switch (_dir)
	{
	case eDir::Up:
		strDir = L"bazzi_up";
		break;
	case eDir::Down:
		strDir = L"bazzi_down";
		break;
	case eDir::Left:
		strDir = L"bazzi_left";
		break;
	case eDir::Right:
		strDir = L"bazzi_right";
		break;
	}

	return strDir;
}

// 부활하거나 내린 후에는 일정시간 동안 무적
void CPlayer::GetOffVehicle()
{
	m_bInvincible = true;
	m_bIsRiding = false;
	m_speed = m_prevSpeed;

	m_bIsGettingOff = true;
	m_vehicle->SetAlive(false);
	m_vehicle = nullptr;
}