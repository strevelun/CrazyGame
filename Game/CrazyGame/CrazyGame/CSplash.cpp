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

CSplash::CSplash(const D2D1_RECT_F& _rect, std::string _animClipName) : CObj(_rect)
{
	m_animClip = *(CResourceManager::GetInst()->GetAnimationClip(_animClipName));
	m_animClip.SetFrametimeLimit(0.1f);
	m_animator.AddClip(_animClipName, &m_animClip);
	m_animator.SetClip(_animClipName);

	m_rect = _rect;
	CObj::RectToPos(m_rect, m_cellXPos, m_cellYPos);
}

CSplash::~CSplash()
{
}

void CSplash::Update()
{
	CScene* scene = CSceneManager::GetInst()->GetCurScene();
	CBoard* pBoard = dynamic_cast<CInGameScene*>(scene)->GetBoard();
	
	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Item))
	{
		pBoard->RemoveObj(m_rect);
	}

	if (pBoard->IsGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Balloon))
	{
		CLayer* layer = scene->FindLayer("Event");		
		CObj* obj = layer->FindObj(m_rect);
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
			player->Die();
	}

	m_animator.Update();

	if (m_animClip.GetNumOfFrame() - 1 <= m_animClip.GetCurFrameIdx())
		m_isAlive = false;
}

void CSplash::Render(ID2D1RenderTarget* _pRenderTarget)
{
	tAnimationFrame* frame = m_animClip.GetCurFrame();

	_pRenderTarget->DrawBitmap(CResourceManager::GetInst()->GetIdxBitmap(frame->bitmapIdx)->GetBitmap(),
		m_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		frame->rect);
}
