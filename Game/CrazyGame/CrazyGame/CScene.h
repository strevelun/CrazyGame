#pragma once

#include "../../D2DCore/CCore.h"
#include <list>
#include <string>

class CLayer;

class CScene
{
protected:		
	std::list<CLayer*> m_layerList;

	std::string m_strName;

private:
	static bool LayerSort(const CLayer* a, const CLayer* b);

public:
	CScene();
	virtual ~CScene();

	virtual void Init();
	virtual void Cleanup();

	virtual void Input();
	virtual void Update();
	virtual void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	CLayer* CreateLayer(const std::string& _strTag, u_int _zOrder);
	CLayer* FindLayer(const std::string& _strTag);

	void SetName(const std::string& _strName) { m_strName = _strName; }
};

