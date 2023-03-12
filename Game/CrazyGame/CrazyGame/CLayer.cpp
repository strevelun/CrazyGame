#include "CLayer.h"
#include "CObj.h"

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
