#include "CLayer.h"
#include "CObj.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CUI.h"

#include <algorithm>

void CLayer::InsertListIterator(std::list<CObj*>& _where, std::list<CObj*>::iterator& _from, std::list<CObj*>::iterator& _to)
{
	CObj* temp = *_from;
	std::list<CObj*>::iterator iterTemp = _from;
	iterTemp++;
	_where.erase(_from);
	_where.insert(_to, temp);
	_from = iterTemp;
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

			bool inserted = false;
			eInGameObjType type = (*iter)->GetType();
			if (type == eInGameObjType::Character
				|| type == eInGameObjType::Monster
				|| type == eInGameObjType::Boss)
			{
				std::list<CObj*>::iterator it = m_objList.begin();
				std::list<CObj*>::iterator itEnd = m_objList.end();

				for (; it != itEnd;)
				{
					if (((CGameObj*)*it)->GetPoint().y > ((CGameObj*)*iter)->GetPoint().y)
					{
						InsertListIterator(m_objList, iter, it);
						inserted = true;
						break;
					}
					it++;
				}
				if (it == itEnd)
				{
					InsertListIterator(m_objList, iter, it);
					inserted = true;
				}
			}
			if(!inserted)
				++iter;
		}
	}

	//if (m_strTag.compare(L"Block") == 0)
	//	m_objList.sort(CLayer::ObjYPosSort);
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

bool CLayer::ObjYPosSort(CObj* _obj1, CObj* _obj2)
{
	return ((CGameObj*)_obj1)->GetPoint().y < ((CGameObj*)_obj2)->GetPoint().y;
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

CGameObj* CLayer::FindGameObj(int _xpos, int _ypos)
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	for (; iter != iterEnd; iter++)
	{
		D2D1_POINT_2U point = ((CGameObj*)*iter)->GetPoint();
		if (point.x == _xpos && point.y == _ypos)
			return (CGameObj*)*iter;
	}

	return nullptr;
}
