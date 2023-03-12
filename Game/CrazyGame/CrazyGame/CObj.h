#pragma once

#include <d2d1.h>

class CBitmap;

class CObj
{
protected:
	CBitmap*		m_pBitmap;
	D2D1_RECT_F		m_rect;
	D2D1_SIZE_F		m_size;

public:
	CObj();
	~CObj();

	void SetBitmap(CBitmap* _bitmap) { m_pBitmap = _bitmap; }
	void SetPos(D2D1_RECT_F _rect){ m_rect = _rect; }

	void Input();
	void Update();
	void Render(ID2D1RenderTarget* _pRenderTarget);
};

