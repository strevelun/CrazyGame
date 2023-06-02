#include "CBlock.h"
#include "CItem.h"
#include "CResourceManager.h"
#include "CBitmap.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CAnimator.h"
#include "CAnimationClip.h"
#include "CTimer.h"

#include <random>

CBlock::CBlock(const D2D1_RECT_F& _rect) : CStaticObj( _rect )
{
	//m_pItem = new CItem();
	m_eType = eInGameObjType::Block_Destructible; // �ϴ� �ı������� ������� ����
	m_eBlockState = eBlockState::Idle;
}

CBlock::~CBlock()
{
}

void CBlock::Update()
{
	float deltaTime = CTimer::GetInst()->GetDeltaTime();

	if (m_eBlockState == eBlockState::Moving)
	{
 		m_rect.left += 210 * deltaTime * m_dirX;
		m_rect.right += 210 * deltaTime * m_dirX;
		m_rect.top += 210 * deltaTime * m_dirY;
		m_rect.bottom += 210 * deltaTime * m_dirY;

		if (m_dirX == -1 && (m_cellXPos + m_dirX) * BOARD_BLOCK_SIZE + 20 >= m_rect.left) // �������� �о�����
		{
			m_rect.left = (m_cellXPos + m_dirX)* BOARD_BLOCK_SIZE + 20;
			m_rect.right = m_rect.left + BOARD_BLOCK_SIZE;
			m_eBlockState = eBlockState::Idle;
			m_cellXPos += m_dirX;
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->RemoveObj(m_cellXPos, m_cellYPos, L"Event", eInGameObjType::Item);
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->PutObj(m_cellXPos, m_cellYPos, this, eInGameObjType::Block_Destructible);
		}
		else if (m_dirX == 1 && (m_cellXPos + m_dirX) * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 20 <= m_rect.right) // ���������� �о�����
		{
			m_rect.left = (m_cellXPos + m_dirX) * BOARD_BLOCK_SIZE + 20;
			m_rect.right = m_rect.left + BOARD_BLOCK_SIZE;
			m_eBlockState = eBlockState::Idle;
			m_cellXPos += m_dirX;
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->RemoveObj(m_cellXPos, m_cellYPos, L"Event", eInGameObjType::Item);
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->PutObj(m_cellXPos, m_cellYPos, this, eInGameObjType::Block_Destructible);
		}
		else if (m_dirY == -1 && (m_cellYPos + m_dirY) * BOARD_BLOCK_SIZE + 40 >= m_rect.top) // �������� �о�����
		{
			m_rect.bottom = (m_cellYPos + m_dirY) * BOARD_BLOCK_SIZE + 40 + BOARD_BLOCK_SIZE;
			m_rect.top = m_rect.bottom - m_size.height;
			m_eBlockState = eBlockState::Idle;
			m_cellYPos += m_dirY;
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->RemoveObj(m_cellXPos, m_cellYPos, L"Event", eInGameObjType::Item);
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->PutObj(m_cellXPos, m_cellYPos, this, eInGameObjType::Block_Destructible);
		}
		else if (m_dirY == 1 && (m_cellYPos + m_dirY) * BOARD_BLOCK_SIZE + BOARD_BLOCK_SIZE + 40 <= m_rect.bottom) // �Ʒ������� �о�����
		{
			m_rect.bottom = (m_cellYPos + m_dirY) * BOARD_BLOCK_SIZE + 40 + BOARD_BLOCK_SIZE;
			m_rect.top = m_rect.bottom - m_size.height;
			m_eBlockState = eBlockState::Idle;
			m_cellYPos += m_dirY;
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->RemoveObj(m_cellXPos, m_cellYPos, L"Event", eInGameObjType::Item);
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->PutObj(m_cellXPos, m_cellYPos, this, eInGameObjType::Block_Destructible);
		}
	}
}

void CBlock::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	_pRenderTarget->DrawBitmap(
		CResourceManager::GetInst()->GetIdxBitmap(m_sprite->idx)->GetBitmap(),
		m_rect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_sprite->rect);
}

void CBlock::Move(eDir _eDir)
{
	// �÷��̾ 0.5�� �̻� ����� �и�, �ڵ����� ��ĭ ������ �̵�
	if (_eDir == eDir::None)
	{
		m_moveTime = 0.0f;
		return;
	}

	m_dirX = 0, m_dirY = 0;
	if (_eDir == eDir::Left) m_dirX = -1;
	else if (_eDir == eDir::Right) m_dirX = 1;
	if (_eDir == eDir::Up) m_dirY = -1;
	if (_eDir == eDir::Down) m_dirY = 1;
	
	if (((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->IsMovable(m_cellXPos + m_dirX, m_cellYPos + m_dirY))
	{
		m_moveTime += CTimer::GetInst()->GetDeltaTime();
		if (m_moveTime >= m_moveTimeLimit)
		{
			((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->PutObj(m_cellXPos, m_cellYPos, this, eInGameObjType::None);

			m_eBlockState = eBlockState::Moving;
			m_moveTime = 0.0f;
		}
	}


}

void CBlock::Die()
{
	// ����� �ı��Ǹ� �� �ڸ����� ���ο� ������ ��ü�� �����ǰ� Render
	// layer�� �ֱ�, board���� eInGameObjType::Item

	std::random_device random;                              
	std::mt19937 engine(random());                        
	std::uniform_int_distribution<int> distribution(0, (int)eItem::Gift_None - 1);
	auto generated = distribution(engine);

	CInGameScene* scene = dynamic_cast<CInGameScene*>(CSceneManager::GetInst()->GetCurScene());

	CLayer* pLayer = CSceneManager::GetInst()->GetCurScene()->FindLayer(L"Event");
	if (pLayer != nullptr)
	{
		m_pItem = new CItem(m_rect, eInGameObjType::Item);
		pLayer->AddObj(m_pItem);
	}

	std::wstring strName;

	generated = 5;

	switch ((eItem)generated)
	{
	case eItem::Gift_Boom:
		strName = L"Gift_Boom";
		break;
	case eItem::Gift_Bubble:
		strName = L"Gift_Bubble";
		break;
	//case eItem::Gift_Dart:
	//	strName = L"Gift_Dart";
	//	break;
	//case eItem::Gift_Devil:
	//	strName = L"Gift_Devil";
	//	break;
	//
	// case eItem::Gift_Owl:
	//	strName = L"Gift_Owl";
	//	break;
	case eItem::Gift_Potion:
		strName = L"Gift_Potion";
		break;
	case eItem::Gift_Shoes:
		strName = L"Gift_Shoes";
		break;
	case eItem::Gift_Skate:
		strName = L"Gift_Skate";
		break;
	//case eItem::Gift_Turtle:
		//strName = L"Gift_Turtle";
		//break;
	case eItem::Gift_UFO:
		strName = L"Gift_UFO";
		break;
	}

	m_pItem->Init(eItem::Gift_UFO, strName);
	
	scene->m_board->SetInGameObjType(m_cellXPos, m_cellYPos, eInGameObjType::Item);
	scene->m_board->PutItem(m_rect, m_pItem);
}
