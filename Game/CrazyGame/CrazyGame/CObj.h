#pragma once

#include <d2d1.h>
#include <list>
#include "CLayer.h"
#include "Setting.h"

class CBitmap;
class CLayer;
class CAnimator;

/*
class CObj
{
protected:
	D2D1_RECT_F						m_rect;
	D2D1_SIZE_U						m_size;

	std::string m_strName;
};
*/


class CObj
{
protected:
	friend class CLayer;

	std::string m_strName;

	D2D1_RECT_F						m_rect;
	D2D1_SIZE_U						m_size;
	eInGameObjType					m_eType;

	int m_cellXPos, m_cellYPos;
	int m_prevCellXPos, m_prevCellYPos;

	bool m_isAlive = true;

public:
	CObj();
	CObj(const D2D1_RECT_F& _rect);
	virtual ~CObj();

	//void SetAnimation(CAnimator* _anim) { m_pAnim = _anim; }

	D2D1_RECT_F GetRect() const { return m_rect; }
	eInGameObjType GetType() const { return m_eType; }

	D2D1_POINT_2U GetPoint() const { return D2D1::Point2U(m_cellXPos, m_cellYPos); }

	template <typename T>
	static T* CreateObj(CLayer* _pLayer = nullptr);
	static void RectToPos(D2D1_RECT_F _rect, int& _x, int& _y);

	virtual void Input();
	virtual void Update();
	virtual void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	void SetAlive(bool _isAlive) { m_isAlive = _isAlive; }
	
	bool IsAlive() const { return m_isAlive; }

	virtual void Die();
};

template<typename T>
inline T* CObj::CreateObj(CLayer* _pLayer)
{
	T* obj = new T;

	if (_pLayer) _pLayer->AddObj(obj);

	return obj;
}
