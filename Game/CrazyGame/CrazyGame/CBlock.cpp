#include "CBlock.h"
#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CAnimation.h"
#include "CAnimationClip.h"

CBlock::CBlock()
{
	//m_pItem = new CItem();
}

CBlock::~CBlock()
{
}

void CBlock::Render(ID2D1RenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(
		CResourceManager::GetInst()->GetIdxBitmap(m_sprite->idx)->GetBitmap(),
		m_rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_sprite->rect);
}

void CBlock::Die()
{
	// 블록이 파괴되면 그 자리에서 새로운 아이템 객체가 생성되고 Render
	// layer에 넣기, board에는 eInGameObjType::Item

	CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
	if(pLayer != nullptr)
		m_pItem = CObj::CreateObj<CItem>(pLayer);
	m_pItem->SetRect(m_rect);
	
	CAnimation* anim = new CAnimation();
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip("Gift_Boom");
	animClip->SetFrametimeLimit(0.2f);
	anim->AddClip("Gift_Boom", animClip);
	anim->SetClip("Gift_Boom");
	m_pItem->SetAnimation(anim);
	//dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetCurScene())->m_board->SetInGameObjType()
}
