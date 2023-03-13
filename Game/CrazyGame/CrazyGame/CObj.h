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

	std::string m_strName;

public:
	CObj();
	~CObj();

	void SetBitmap(CBitmap* _bitmap) { m_pBitmap = _bitmap; }
	void SetRect(D2D1_RECT_F _rect){ m_rect = _rect; }

	D2D1_RECT_F GetRect() const { return m_rect; }

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

	return obj;
}
