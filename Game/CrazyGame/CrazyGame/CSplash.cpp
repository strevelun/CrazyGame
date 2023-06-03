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

// ���÷��ð� ���� �� ��� ������Ʈ�� �ϰ� �ִ� ��Ȳ���� ���÷��ð� Die �� ����� ������ Item�� �� �ڸ��� ������ PutItem(nullptr)�� �ع����� �÷��̾ �������� ���� �� ���� ��Ȳ�� ����
// �� ��ǳ���� �Ϸķ� �������� ������ �� ���¿��� ���ٱⰡ 8�̰�, ���� ������ ��ǳ���� ���� ���� ����� �μ��� PutItem(nullptr)
// (�÷��̾ ���ʿ��� ���������� ���鼭 ��ǳ���� ���������� ����. ���� ��ǳ���� ���� ������. �׷��� ������ ��ǳ���� ������ �����¿�� ���÷��ø� ���´�. 
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
