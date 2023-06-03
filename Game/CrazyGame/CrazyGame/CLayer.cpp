#include "CLayer.h"
#include "CObj.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CUI.h"

#include <algorithm>

void CLayer::SortYPosMoveObj()
{
	std::list<CObj*> tempList;
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	CObj* pPlayer = nullptr;

	for (; iter != iterEnd;)
	{
		eInGameObjType type = (*iter)->GetType();
		if (type == eInGameObjType::Character || type == eInGameObjType::Monster || type == eInGameObjType::Boss || type == eInGameObjType::Balloon || type == eInGameObjType::Block_Destructible || type == eInGameObjType::Item)
		{
			if (type == eInGameObjType::Character && ((CPlayer*)(*iter))->GetVehicle() != nullptr)
			{
				pPlayer = * iter;
				iter = m_objList.erase(iter);
				continue; // 플레이어가 우주선 탑승 중이면 맨 뒤로
			}
			tempList.push_back(*iter);
			iter = m_objList.erase(iter);
		}
		else
			iter++;
	}

	if (pPlayer != nullptr)
		tempList.push_back(pPlayer);

	std::list<CObj*>::iterator it = tempList.begin();
	std::list<CObj*>::iterator itEnd = tempList.end();

	while (it != itEnd)
	{
		iter = m_objList.begin();

		for (; iter != iterEnd; iter++)
		{
			if (((CGameObj*)*iter)->GetPoint().y > ((CGameObj*)*it)->GetPoint().y)
			{
				m_objList.insert(iter, *it);
				break;
			}
		}

		if (iter == iterEnd)
			m_objList.insert(iter, *it);

		it++;
	}
}

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

void CLayer::Input()
{
}

void CLayer::Update()
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	for (; iter != iterEnd; )
	{
		if (!(*iter)->IsAlive())
		{
 			(*iter)->Die();
			delete* iter;
			iter = m_objList.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}

	SortYPosMoveObj();
}

void CLayer::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();


	

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Render(_pRenderTarget);	
	}
}

void CLayer::DeleteAllObj()
{
	std::list<CObj*>::iterator iter = m_objList.begin();
 	std::list<CObj*>::iterator iterEnd = m_objList.end();

	for (; iter != iterEnd; iter++)
	{
		delete *iter;
	}

	m_objList.clear();
}

CObj* CLayer::FindObj(D2D1_RECT_F _rect)
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	for (; iter != iterEnd; iter++)
	{
		if ((*iter)->GetRect().left <= _rect.left && _rect.right <= (*iter)->GetRect().right
			&& (*iter)->GetRect().top <= _rect.top && _rect.bottom <= (*iter)->GetRect().bottom)
			return *iter;
	}

	return nullptr;
}

CGameObj* CLayer::FindGameObj(int _xpos, int _ypos, eInGameObjType _type)
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	for (; iter != iterEnd; iter++)
	{
		D2D1_POINT_2U point = ((CGameObj*)*iter)->GetPoint();
		if (point.x == _xpos && point.y == _ypos)
		{
			if (_type == eInGameObjType::None || _type == (*iter)->GetType())
				return (CGameObj*)*iter;
		}
	}

	return nullptr;
}
