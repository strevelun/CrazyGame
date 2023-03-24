#include "CBlock.h"
#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CAnimation.h"
#include "CAnimationClip.h"

#include <random>

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

	std::random_device random;                              
	std::mt19937 engine(random());                        
	std::uniform_int_distribution<int> distribution(0, (int)Item::Gift_None - 1);
	auto generated = distribution(engine);

	std::string strName;

	switch ((Item)generated)
	{
	case Item::Gift_Boom:
		strName = "Gift_Boom";
		break;
	case Item::Gift_Bubble:
		strName = "Gift_Bubble";
		break;
	case Item::Gift_Dart:
		strName = "Gift_Dart";
		break;
	case Item::Gift_Devil:
		strName = "Gift_Devil";
		break;
	case Item::Gift_Owl:
		strName = "Gift_Owl";
		break;
	case Item::Gift_Potion:
		strName = "Gift_Potion";
		break;
	case Item::Gift_Shoes:
		strName = "Gift_Shoes";
		break;
	case Item::Gift_Skate:
		strName = "Gift_Skate";
		break;
	case Item::Gift_Turtle:
		strName = "Gift_Turtle";
		break;
	case Item::Gift_UFO:
		strName = "Gift_UFO";
		break;
	}

	CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
	if(pLayer != nullptr)
		m_pItem = CObj::CreateObj<CItem>(pLayer);
	m_pItem->SetRect(m_rect);
	
	CAnimation* anim = new CAnimation();
	CAnimationClip* animClip = CResourceManager::GetInst()->GetAnimationClip(strName);
	animClip->SetFrametimeLimit(0.2f);
	anim->AddClip(strName, animClip);
	anim->SetClip(strName);
	m_pItem->SetAnimation(anim);
	m_pItem->SetItemName(strName);
	int x, y;
	CObj::RectToPos(m_rect, x, y);
	dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetCurScene())->m_board->SetInGameObjType(x, y, eInGameObjType::Item);
}
