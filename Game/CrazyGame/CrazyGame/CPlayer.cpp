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


CPlayer::CPlayer(const D2D1_RECT_F& _rect) : CMoveObj(_rect)
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
	animClip->SetFrametimeLimit(0.2f);
	m_pAnim->AddClip("bazzi_ready", animClip);
	m_pAnim->SetClip("bazzi_ready");

	for (int i = 0; i < (int)Dir::None; i++)
	{
		m_animDir[i] = m_pAnim->GetClip(GetStrDir((Dir)i));
	}
}

CPlayer::~CPlayer()
{
	// bazzi_die만 따로 해제
	delete m_pAnim->GetClip("bazzi_die");
}


void CPlayer::Input()
{
	if (m_state == Player_State::Ready || m_state == Player_State::Die)
		return;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_eMoveDir = Dir::Left;
		m_eLastMoveDir = m_eMoveDir;
		m_state = Player_State::Move;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_eMoveDir = Dir::Right;
		m_eLastMoveDir = m_eMoveDir;
		m_state = Player_State::Move;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_eMoveDir = Dir::Up;
		m_eLastMoveDir = m_eMoveDir;
		m_state = Player_State::Move;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_eMoveDir = Dir::Down;
		m_eLastMoveDir = m_eMoveDir;
		m_state = Player_State::Move;
	}
	else
	{
		m_eMoveDir = Dir::None;
		m_state = Player_State::Idle;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_bFire = true;
	}
}

void CPlayer::Update()
{
	CObj::Update();
	m_pAnim->GetCurClip()->Update();

	CObj::RectToPos(m_rect, m_xpos, m_ypos);

#ifdef _DEBUG
	char str[50] = "";
	sprintf_s(str, "%d, %d\n", m_xpos, m_ypos);
	OutputDebugStringA(str);
#endif

	CBoard* board = ((CInGameScene*)m_pScene)->m_board;

	// 현재 != 이전 상태 : PlayClip 

	switch (m_state)
	{
	case Player_State::Ready:
		m_pAnim->SetClip("bazzi_ready");

		break;
	case Player_State::Idle:
		break;
	case Player_State::Move:
		MoveOnMoveObjBoard(eInGameObjType::Character);
		MoveState();
		break;
	case Player_State::Die:
		//m_pAnim->PlayClip("bazzi_die");
		break;
	}

	CItem* item = board->GetItem(m_rect);

	if (item)
	{
		switch (item->GetItemEnum())
		{
		case eItem::Gift_Skate:
			m_speed += 100;
			break;
		case eItem::Gift_Turtle:
			break;
		case eItem::Gift_UFO:
			break;
		case eItem::Gift_Boom:
			break;
		case eItem::Gift_Bubble:
			break;
		case eItem::Gift_Dart:
			break;
		case eItem::Gift_Devil:
			break;
		case eItem::Gift_Owl:
			break;
		case eItem::Gift_Potion:
			break;
		case eItem::Gift_Shoes:
			break;
		}
	}

	if (m_bFire)
	{
		CBubble* bubble = new CBubble({
			(float)m_xpos * BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)m_ypos * BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)m_xpos* BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 20 * ((float)BOARD_BLOCK_SIZE / 40),
			(float)m_ypos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40 * ((float)BOARD_BLOCK_SIZE / 40)
			});
		D2D1_POINT_2U point = bubble->GetPoint();
		((CInGameScene*)m_pScene)->m_board->PutObj(point.x, point.y, bubble, eInGameObjType::Balloon);
		m_bFire = false;
	}
}

void CPlayer::Render(ID2D1RenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = nullptr;
	tAnimationFrame* frame = nullptr;

	switch (m_state)
	{
	case Player_State::Ready:
		clip = m_pAnim->GetClip("bazzi_ready");
		if (!clip) return;
		frame = clip->GetCurFrame();

		if (clip->IsCurClipEnd())
		{
			m_state = Player_State::Idle;
			return;
		}
	break;
	case Player_State::Idle:
		clip = m_animDir[(int)m_eLastMoveDir];
		if (!clip) return;
		frame = clip->GetFirstFrame();
		break;
	case Player_State::Move:
		clip = m_animDir[(int)m_eLastMoveDir];
		if (!clip) return;
		frame = clip->GetCurFrame();
		break;
	case Player_State::Die:
		clip = m_pAnim->GetClip("bazzi_die");
		if (!clip) return;
		frame = clip->GetCurFrame();

		if (clip->IsCurClipEnd())
		{
			m_isAlive = false;
			return;
		}
		break;
	}

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}

void CPlayer::Die()
{
	m_state = Player_State::Die;
	//MessageBox(NULL, L"사망", L"사망", MB_OK);

}

void CPlayer::MoveState()
{
	int stageFrameOffsetX = 20 * ((float)BOARD_BLOCK_SIZE / 40);
	int stageFrameOffsetY = 40 * ((float)BOARD_BLOCK_SIZE / 40);
	int left = m_rect.left - stageFrameOffsetX;
	int right = m_rect.right - stageFrameOffsetX;
	int top = m_rect.top - stageFrameOffsetY;
	int bottom = m_rect.bottom - stageFrameOffsetY;
	CBoard* board = ((CInGameScene*)m_pScene)->m_board;
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	int x = 0, y = 0;

	// 블록 위에 있으면 돌아다닐 수 있음
	if (m_eMoveDir == Dir::Left)
	{
		if (board->IsMovable(left - m_speed * deltaTime, bottom - (BOARD_BLOCK_SIZE * 0.1f), false)
			&& board->IsMovable(left - m_speed * deltaTime, top + (BOARD_BLOCK_SIZE * 0.5f), false)
			|| board->IsGameObjType(m_xpos, m_ypos, eInGameObjType::Balloon))
		{
			x = -1;
			m_pAnim->SetClip("bazzi_left"); 
		}
	}
	else if (m_eMoveDir == Dir::Right)
	{
		if (board->IsMovable(right + m_speed * deltaTime, bottom - (BOARD_BLOCK_SIZE * 0.1f), false)
			&& board->IsMovable(right + m_speed * deltaTime, top + (BOARD_BLOCK_SIZE * 0.5f), false)
			|| board->IsGameObjType(m_xpos, m_ypos, eInGameObjType::Balloon))
		{
			x = 1;
			m_pAnim->SetClip("bazzi_right");
		}
	}
	else if (m_eMoveDir == Dir::Up)
	{
		if (board->IsMovable(left + (BOARD_BLOCK_SIZE * 0.1f), top - m_speed * deltaTime + (BOARD_BLOCK_SIZE * 0.5f), false)
			&& board->IsMovable(right - (BOARD_BLOCK_SIZE * 0.1f), top - m_speed * deltaTime + (BOARD_BLOCK_SIZE * 0.5f), false)
			|| board->IsGameObjType(m_xpos, m_ypos, eInGameObjType::Balloon))
		{
			y = -1;
			m_pAnim->SetClip("bazzi_up");
		}
	}
	else if (m_eMoveDir == Dir::Down)
	{
		if (board->IsMovable(left + (BOARD_BLOCK_SIZE * 0.1f), bottom + m_speed * deltaTime, false)
			&& board->IsMovable(right - (BOARD_BLOCK_SIZE * 0.1f), bottom + m_speed * deltaTime, false)
			||  board->IsGameObjType(m_xpos, m_ypos, eInGameObjType::Balloon))
		{
			y = 1;
			m_pAnim->SetClip("bazzi_down");
		}
	}

	m_rect.left += m_speed * deltaTime * x;
	m_rect.right += m_speed * deltaTime * x;
	m_rect.top += m_speed * deltaTime * y;
	m_rect.bottom += m_speed * deltaTime * y;
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
