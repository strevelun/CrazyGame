#pragma once

#include "../../D2DCore/CCore.h"
#include <list>
#include <string>

class CLayer;

class CScene
{
	std::list<CLayer*> m_layerList;

private:
	static bool LayerSort(const CLayer* a, const CLayer* b);

public:
	CScene();
	~CScene();
	virtual void Input();
	virtual void Update();
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);

	CLayer* CreateLayer(const std::string& _strTag, u_int _zOrder);
	void Clean();
};

