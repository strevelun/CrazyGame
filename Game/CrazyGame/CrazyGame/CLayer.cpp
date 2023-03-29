#include "CLayer.h"
#include "CObj.h"
#include "CSceneManager.h"
#include "CInGameScene.h"
#include "CPlayer.h"

#include <algorithm>

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

void CLayer::Input()
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Input();
	}
}

void CLayer::Update()
{
	std::list<CObj*>::iterator iter = m_objList.begin();
	std::list<CObj*>::iterator iterEnd = m_objList.end();

	if (m_strTag.compare("Block") == 0)
		m_objList.sort(CLayer::ObjYPosSort);

	for (; iter != iterEnd; )
	{
		if (!(*iter)->IsAlive())
		{
			//((CInGameScene*)CSceneManager::GetInst()->GetCurScene())->m_board->RemoveObj((*iter)->GetRect());
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
}

void CLayer::Render(ID2D1RenderTarget* _pRenderTarget)
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
	return _obj1->GetRect().bottom < _obj2->GetRect().bottom;
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
