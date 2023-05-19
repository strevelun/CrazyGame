#pragma once

#include <list>
#include <d2d1.h>
#include <string>

class CObj;
class CScene;
class CGameObj;
class CUI;

class CLayer // ºÐ¸®
{
private:
	std::list<CGameObj*>	m_gameObjList;
	std::list<CUI*>			m_uiObjList;
	std::wstring			m_strTag;
	u_int				m_zOrder;

public:
	CLayer();
	~CLayer();
	void Input();
	void Update();
	void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	static bool ObjYPosSort(CObj* _obj1, CObj* _obj2);

	void SetZOrder(u_int _zOrder) { m_zOrder = _zOrder; }
	void SetTag(std::wstring _strTag) { m_strTag = _strTag; }
	void AddGameObj(CGameObj* _obj) { m_gameObjList.push_back(_obj); }
	void AddUIObj(CUI* _obj) { m_uiObjList.push_back(_obj); }

	u_int GetZOrder() const { return m_zOrder; }
	std::wstring GetTag() const { return m_strTag; }
	void DeleteAllObj();

	CObj* FindObj(D2D1_RECT_F _rect);
	CObj* FindObj(int _xpos, int _ypos);
};

