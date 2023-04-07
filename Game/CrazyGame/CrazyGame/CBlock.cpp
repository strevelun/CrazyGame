#include "CBlock.h"
#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CAnimator.h"
#include "CAnimationClip.h"

#include <random>

CBlock::CBlock(const D2D1_RECT_F& _rect) : CStaticObj( _rect )
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
	std::uniform_int_distribution<int> distribution(0, (int)eItem::Gift_None - 1);
	auto generated = distribution(engine);

	CInGameScene* scene = dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetCurScene());

	CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer("Event");
	if (pLayer != nullptr)
	{
		m_pItem = new CItem(m_rect);
		pLayer->AddObj(m_pItem);
	}

	std::string strName;

	switch ((eItem)generated)
	{
	case eItem::Gift_Boom:
		strName = "Gift_Boom";
		break;
	case eItem::Gift_Bubble:
		strName = "Gift_Bubble";
		break;
	case eItem::Gift_Dart:
		strName = "Gift_Dart";
		break;
	case eItem::Gift_Devil:
		strName = "Gift_Devil";
		break;
	case eItem::Gift_Owl:
		strName = "Gift_Owl";
		break;
	case eItem::Gift_Potion:
		strName = "Gift_Potion";
		break;
	case eItem::Gift_Shoes:
		strName = "Gift_Shoes";
		break;
	case eItem::Gift_Skate:
		strName = "Gift_Skate";
		break;
	case eItem::Gift_Turtle:
		strName = "Gift_Turtle";
		break;
	case eItem::Gift_UFO:
		strName = "Gift_UFO";
		break;
	}

	m_pItem->Init((eItem)generated, strName);
	
	scene->m_board->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Item);
	scene->m_board->PutItem(m_rect, m_pItem);
}
