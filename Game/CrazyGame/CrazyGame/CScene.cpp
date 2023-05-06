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
	
	
	
}

void CScene::Init()
{
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
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->Update();
	}
}

void CScene::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
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
	CLayer* layer = FindLayer(_strTag);

	if (layer != nullptr)
	{
		return layer;
	}
		

	layer = new CLayer;
	layer->SetTag(_strTag);
	layer->SetZOrder(_zOrder);

	m_layerList.push_back(layer);

	m_layerList.sort(LayerSort);

	return layer;
}

CLayer* CScene::FindLayer(const std::string& _strTag)
{
	std::list<CLayer*>::iterator iter = m_layerList.begin();
	std::list<CLayer*>::iterator iterEnd = m_layerList.end();

	for (; iter != iterEnd; iter++)
	{
		if (_strTag.compare((*iter)->GetTag()) == 0)
			return *iter;
	}

	return nullptr;
}

void CScene::Clean()
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