#pragma once

#include <list>
#include <d2d1.h>
#include <string>

class CObj;
class CScene;
class CGameObj;
class CUI;

class CLayer // 분리
{
private:
	std::list<CObj*>	m_objList;
	std::wstring			m_strTag;
	u_int				m_zOrder;

private:
	// iter위치의 원소를 it위치로 삽입
	void InsertListIterator(std::list<CObj*>& _where, std::list<CObj*>::iterator& _from, std::list<CObj*>::iterator& _to);

public:
	CLayer();
	~CLayer();
	void Input();
	void Update();
	void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	static bool ObjYPosSort(CObj* _obj1, CObj* _obj2);

	void SetZOrder(u_int _zOrder) { m_zOrder = _zOrder; }
	void SetTag(std::wstring _strTag) { m_strTag = _strTag; }
	void AddObj(CObj* _obj) { m_objList.push_back(_obj); }

	u_int GetZOrder() const { return m_zOrder; }
	std::wstring GetTag() const { return m_strTag; }
	void DeleteAllObj();

	CObj* FindObj(D2D1_RECT_F _rect);
	CGameObj* FindGameObj(int _xpos, int _ypos);
};

