#pragma once

#include <d2d1.h>
#include <list>
#include "CLayer.h"

class CBitmap;
class CLayer;

class CObj
{
protected:
	CBitmap*						m_pBitmap;
	D2D1_RECT_F						m_rect;
	D2D1_SIZE_U						m_size;
	static std::list<CObj*>			m_objList;

public:
	CObj();
	~CObj();

	void SetBitmap(CBitmap* _bitmap) { m_pBitmap = _bitmap; }
	void SetPos(D2D1_RECT_F _rect){ m_rect = _rect; }
	template <typename T>
	static T* CreateObj(CLayer* _pLayer = nullptr);

	virtual void Input();
	virtual void Update();
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);
};

template<typename T>
inline T* CObj::CreateObj(CLayer* _pLayer)
{
	T* obj = new T;

	if (_pLayer) _pLayer->AddObj(obj);
	m_objList.push_back(obj);

	return obj;
}
