#pragma once

#include <list>
#include <d2d1.h>
#include <string>

class CObj;

class CLayer
{
private:
	std::list<CObj*>	m_objList;
	std::string			m_strTag;
	u_int				m_zOrder;

public:
	CLayer();
	~CLayer();
	void Input();
	void Update();
	void Render(ID2D1RenderTarget* _pRenderTarget);

	void SetZOrder(u_int _zOrder) { m_zOrder = _zOrder; }
	void SetTag(std::string _strTag) { m_strTag = _strTag; }
	void AddObj(CObj* _obj) { m_objList.push_back(_obj); }

	u_int GetZOrder() const { return m_zOrder; }
	std::string GetTag() const { return m_strTag; }
	void DeleteAllObj();
};

