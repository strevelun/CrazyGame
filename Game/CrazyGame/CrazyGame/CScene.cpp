#include "CScene.h"
#include "CLayer.h"

bool CScene::LayerSort(const CLayer* a, const CLayer* b)
{
	return a->GetZOrder() < b->GetZOrder();
}

CScene::CScene()
{
}

CScene::~CScene()
{
	
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->DeleteAllObj();
		delete* iter;
	}
	m_layerList.clear();
	
}

void CScene::Input()
{
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Input();
	}
}

void CScene::Update()
{
}

void CScene::Render(ID2D1RenderTarget* _pRenderTarget)
{
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Render(_pRenderTarget);
	}
}

CLayer* CScene::CreateLayer(const std::string& _strTag, u_int _zOrder)
{
	CLayer* layer = new CLayer;
	layer->SetTag(_strTag);
	layer->SetZOrder(_zOrder);

	m_layerList.push_back(layer);

	m_layerList.sort(LayerSort);

	return layer;
}
