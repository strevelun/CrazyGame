#include "CSplash.h"
#include "CAnimationClip.h"
#include "CResourceManager.h"
#include "CAnimator.h"
#include "CBitmap.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CBoard.h"
#include "CItem.h"
#include "CPlayer.h"
#include "CVehicle.h"
#include "CBoss.h"
#include "CMoveObj.h"

CSplash::CSplash(const D2D1_RECT_F& _rect, std::wstring _animClipName, CMoveObj* _pOwner) : CStaticObj(_rect)
{
	m_animClip = *(CResourceManager::GetInst()->GetAnimationClip(_animClipName));
	m_animClip.SetFrametimeLimit(0.1f);
	m_anim.AddClip(_animClipName, &m_animClip);
	m_anim.SetClip(_animClipName);

	m_rect = _rect;
	CObj::RectToPos(m_rect, m_cellXPos, m_cellYPos);
	m_pOwner = _pOwner;
}

CSplash::~CSplash()
{
}

// 스플레시가 생성 후 계속 업데이트를 하고 있는 상황에서 스플래시가 Die 전 블록이 없어져 Item을 그 자리에 놓으면 PutItem(nullptr)을 해버려서 플레이어가 아이템을 먹을 수 없는 상황이 생김
// 즉 물풍선을 일렬로 놓았을때 ㅁㅇㅇ 인 상태에서 물줄기가 8이고, 가장 오른쪽 물풍선이 가장 왼쪽 블록을 부수면 PutItem(nullptr)
// (플레이어가 왼쪽에서 오른쪽으로 가면서 물풍선을 놓았을떄를 가정. 왼쪽 물풍선이 먼저 터진다. 그러면 오른쪽 물풍선이 터질때 상하좌우로 스플래시를 놓는다. 
void CSplash::Update()
{
	CScene* scene = CSceneManager::GetInst()->GetCurScene();
	CBoard* pBoard = dynamic_cast<CInGameScene*>(scene)->GetBoard();
	
	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Item))
	{
		pBoard->RemoveObj(m_cellXPos, m_cellYPos, L"Event", eInGameObjType::Item);
		//pBoard->PutItem(m_cellXPos, m_cellYPos, nullptr);
	}

	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon))
	{
		CLayer* layer = scene->FindLayer(L"Event");		
		CObj* obj = layer->FindGameObj(m_cellXPos, m_cellYPos);
		if (obj)
		{
			obj->SetAlive(false);
			pBoard->RemoveObj(m_rect);
		}
	}

	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Character))
	{
		CPlayer* player = dynamic_cast<CInGameScene*>(scene)->GetPlayer();
		if (player)
		{
			if (player->GetVehicle() == nullptr)
				player->Hit();
			else
				player->GetOffVehicle();
		}
	}

	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Monster))
	{
		if (m_pOwner->GetType() == eInGameObjType::Character)
		{
			CMoveObj* obj = pBoard->GetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos);
			obj->Die();
		}
	}
	/*
	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Boss))
	{
		CLayer* pLayer = scene->FindLayer(L"Block");
		//if (pLayer)
		{
			//CBoss* pBoss = reinterpret_cast<CBoss*>(pLayer->FindObj(m_cellXPos, m_cellYPos));
			CBoss* pBoss = (CBoss*)pBoard->GetObjTypeInMoveObjBoard(m_cellXPos, m_cellYPos);
			pBoss->Hit();
		}
	}
	*/

	m_anim.Update();

	CAnimationClip* clip = m_anim.GetCurClip();
	if (!clip) return;

	if (clip->IsCurClipEnd())
	{
		m_isAlive = false;
		return;
	}
}

void CSplash::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	m_anim.Render(_pRenderTarget, m_rect);
}
