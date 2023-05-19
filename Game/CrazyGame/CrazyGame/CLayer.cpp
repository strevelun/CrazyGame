#include "CLayer.h"
#include "CObj.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CUI.h"

#include <algorithm>

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

void CLayer::Input()
{
	std::list<CGameObj*>::iterator iter = m_gameObjList.begin();
	std::list<CGameObj*>::iterator iterEnd = m_gameObjList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Input();
	}

	std::list<CUI*>::iterator iter1 = m_uiObjList.begin();
	std::list<CUI*>::iterator iterEnd1 = m_uiObjList.end();

	for (; iter1 != iterEnd1; iter1++)
	{
		(*iter1)->Input();
	}
}

void CLayer::Update()
{
	std::list<CGameObj*>::iterator iter = m_gameObjList.begin();
	std::list<CGameObj*>::iterator iterEnd = m_gameObjList.end();

	if (m_strTag.compare(L"Block") == 0)
		m_gameObjList.sort(CLayer::ObjYPosSort);

	for (; iter != iterEnd; )
	{
		if (!(*iter)->IsAlive())
		{
			//((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->RemoveObj((*iter)->GetRect());
			(*iter)->Die();
			delete* iter;
			iter = m_gameObjList.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}

	std::list<CUI*>::iterator iter1 = m_uiObjList.begin();
	std::list<CUI*>::iterator iterEnd1 = m_uiObjList.end();

	for (; iter1 != iterEnd1; )
	{
		if (!(*iter1)->IsAlive())
		{
			(*iter1)->Die();
			delete* iter1;
			iter1 = m_uiObjList.erase(iter1);
		}
		else
		{
			(*iter1)->Update();
			++iter1;
		}
	}
}

void CLayer::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
{
	std::list<CGameObj*>::iterator iter = m_gameObjList.begin();
	std::list<CGameObj*>::iterator iterEnd = m_gameObjList.end();


	for (; iter != iterEnd; iter++)
	{
		(*iter)->Render(_pRenderTarget);	
	}

	std::list<CUI*>::iterator iter1 = m_uiObjList.begin();
	std::list<CUI*>::iterator iterEnd1 = m_uiObjList.end();

	for (; iter1 != iterEnd1; iter1++)
	{
		(*iter1)->Render(_pRenderTarget);
	}
}

bool CLayer::ObjYPosSort(CObj* _obj1, CObj* _obj2)
{
	return _obj1->GetRect().bottom < _obj2->GetRect().bottom;
}

void CLayer::DeleteAllObj()
{
	std::list<CGameObj*>::iterator iter = m_gameObjList.begin();
 	std::list<CGameObj*>::iterator iterEnd = m_gameObjList.end();

	for (; iter != iterEnd; iter++)
	{
		delete *iter;
	}

	m_gameObjList.clear();

	std::list<CUI*>::iterator iter1 = m_uiObjList.begin();
	std::list<CUI*>::iterator iterEnd1 = m_uiObjList.end();

	for (; iter1 != iterEnd1; iter1++)
	{
		delete* iter1;
	}

	m_uiObjList.clear();
}

CObj* CLayer::FindObj(D2D1_RECT_F _rect)
{
	std::list<CGameObj*>::iterator iter = m_gameObjList.begin();
	std::list<CGameObj*>::iterator iterEnd = m_gameObjList.end();

	for (; iter != iterEnd; iter++)
	{
		if ((*iter)->GetRect().left <= _rect.left && _rect.right <= (*iter)->GetRect().right
			&& (*iter)->GetRect().top <= _rect.top && _rect.bottom <= (*iter)->GetRect().bottom)
			return *iter;
	}

	return nullptr;
}

// UI 대상으로 호출 안함
CObj* CLayer::FindObj(int _xpos, int _ypos)
{
	std::list<CGameObj*>::iterator iter = m_gameObjList.begin();
	std::list<CGameObj*>::iterator iterEnd = m_gameObjList.end();

	for (; iter != iterEnd; iter++)
	{
		D2D1_POINT_2U point = (*iter)->GetPoint();
		if (point.x == _xpos && point.y == _ypos)
			return *iter;
	}

	return nullptr;
}
