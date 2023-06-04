#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CPlayer.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CVehicle.h"

CItem::CItem(const D2D1_RECT_F _rect, eInGameObjType _type) : CStaticObj(_rect)
{
	m_eType = _type;
}

CItem::~CItem()
{
}

void CItem::Init(eItem _eItem, std::wstring _strName)
{
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(_strName);
	animClip->SetFrametimeLimit(0.2f);
	m_anim.AddClip(_strName, animClip);
	m_anim.SetClip(_strName);
	//SetAnimation(anim);
	SetItemName(_strName);
	SetItemEnum((eItem)_eItem);
}

void CItem::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	CAnimationClip* clip = m_anim.GetClip(m_itemName);
	if (!clip) return;
	tAnimationFrame* frame = clip->GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}

void CItem::Benefit(CPlayer* _pPlayer)
{
	int stageFrameOffsetX = 20;
	int stageFrameOffsetY = 40;

	switch (m_eItem)
	{
	case eItem::Gift_Skate:
		if (_pPlayer->m_speed < 280.0f)
			_pPlayer->m_speed += 70;
		break;
	case eItem::Gift_UFO:
	{
		if (_pPlayer->m_vehicle)
			break;

		CInGameScene* scene = (CInGameScene*)CSceneManager::GetInst()->GetCurScene();

		CLayer* layer = scene->FindLayer(L"Vehicle");


		if (layer)
		{
			_pPlayer->m_rideRect = { (float)_pPlayer->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX, (float)_pPlayer->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY, (float)_pPlayer->m_cellXPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetX, (float)_pPlayer->m_cellYPos * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + stageFrameOffsetY };

			_pPlayer->m_rideRect.bottom -= BOARD_BLOCK_SIZE / 3;
			_pPlayer->m_vehicle = new CVehicle(_pPlayer->m_rideRect, L"UFO");
			D2D1_SIZE_U size = _pPlayer->m_vehicle->GetSize();
			_pPlayer->m_rideRect.top = _pPlayer->m_rideRect.bottom - size.height;
			_pPlayer->m_rideRect.left -= (size.width - BOARD_BLOCK_SIZE) / 2;
			_pPlayer->m_rideRect.right -= (size.width - BOARD_BLOCK_SIZE) / 2;
			_pPlayer->m_vehicle->SetRect(_pPlayer->m_rideRect);
			_pPlayer->m_vehicle->SetDir(_pPlayer->m_eMoveDir);

			_pPlayer->m_xpos = (float)_pPlayer->m_cellXPos * BOARD_BLOCK_SIZE + stageFrameOffsetX + (BOARD_BLOCK_SIZE / 2);
			_pPlayer->m_ypos = (float)_pPlayer->m_cellYPos * BOARD_BLOCK_SIZE + stageFrameOffsetY + (BOARD_BLOCK_SIZE / 2);
			_pPlayer->m_rect.left = _pPlayer->m_xpos - (_pPlayer->m_size.width / 3) - 3;
			_pPlayer->m_rect.right = _pPlayer->m_xpos + (_pPlayer->m_size.width / 3) - 3;
			_pPlayer->m_rect.bottom = _pPlayer->m_vehicle->GetRect().top;
			_pPlayer->m_rect.top = _pPlayer->m_rect.bottom - _pPlayer->m_size.height;
			_pPlayer->m_prevSpeed = _pPlayer->m_speed;
			_pPlayer->m_speed = _pPlayer->m_vehicle->GetSpeed();
			_pPlayer->m_bIsRiding = true;
			_pPlayer->m_bIsJumping = true;
		}

	}
	break;
	case eItem::Gift_Boom:
		_pPlayer->m_splashLength = 8;
		break;
	case eItem::Gift_Bubble:
		_pPlayer->m_bubbleCarryLimit += 1;
		break;
	case eItem::Gift_Potion:
		if (_pPlayer->m_splashLength < _pPlayer->m_splashLengthLimit)
			_pPlayer->m_splashLength++;
		break;
	case eItem::Gift_Shoes:
		_pPlayer->m_bKickable = true;
		break;
	}
}

void CItem::Die()
{
	m_isAlive = false;
}
