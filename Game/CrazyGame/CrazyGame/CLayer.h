#pragma once

#include <list>
#include <d2d1.h>
#include <string>

#include "Setting.h"

class CObj;
class CScene;
class CGameObj;
class CUI;

class CLayer // ºÐ¸®
{
private:
	std::list<CObj*>	m_objList;
	std::wstring			m_strTag;
	u_int				m_zOrder;

private:
	void SortYPosMoveObj();

public:
	CLayer();
	~CLayer();
	void Input();
	void Update();
	void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	void SetZOrder(u_int _zOrder) { m_zOrder = _zOrder; }
	void SetTag(std::wstring _strTag) { m_strTag = _strTag; }
	void AddObj(CObj* _obj) { m_objList.push_back(_obj); }

	u_int GetZOrder() const { return m_zOrder; }
	std::wstring GetTag() const { return m_strTag; }
	void DeleteAllObj();

	CObj* FindObj(D2D1_RECT_F _rect);
	CGameObj* FindGameObj(int _xpos, int _ypos, eInGameObjType _type = eInGameObjType::None);
};

