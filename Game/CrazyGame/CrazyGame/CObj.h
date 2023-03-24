#pragma once

#include <d2d1.h>
#include <list>
#include "CLayer.h"
#include "Setting.h"

class CBitmap;
class CLayer;
class CAnimation;

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
	CBitmap*						m_pBitmap;
	D2D1_RECT_F						m_rect;
	D2D1_SIZE_U						m_size;
	tSprite* m_sprite;
	CAnimation* m_pAnim = nullptr;
	bool m_isAlive = true;

	std::string m_strName;

public:
	CObj();
	~CObj();

	void SetBitmap(CBitmap* _bitmap) { m_pBitmap = _bitmap; }
	void SetRect(D2D1_RECT_F _rect){ m_rect = _rect; }
	void SetAnimation(CAnimation* _anim) { m_pAnim = _anim; }

	D2D1_RECT_F GetRect() const { return m_rect; }

	template <typename T>
	static T* CreateObj(CLayer* _pLayer = nullptr);
	static void RectToPos(D2D1_RECT_F _rect, int& _x, int& _y);

	virtual void Input();
	virtual void Update();
	virtual void Render(ID2D1RenderTarget* _pRenderTarget);

	void SetSprite(tSprite* _sprite) { m_sprite = _sprite; }
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
