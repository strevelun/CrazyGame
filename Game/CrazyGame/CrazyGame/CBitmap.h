#pragma once

#include <d2d1.h>

class CBitmap
{
	ID2D1Bitmap* m_pD2dBitmap = nullptr;
	// 비트맵 상에서 이미지 rect
	D2D1_RECT_F m_bitmapRect;
	D2D1_SIZE_F m_bitmapSize;

public:
	CBitmap();
	~CBitmap();

	void SetBitmap(ID2D1Bitmap* _bitmap);
	void SetSize(D2D1_SIZE_F _bitmapSize) { m_bitmapSize = _bitmapSize; }

	ID2D1Bitmap* GetBitmap() const { return m_pD2dBitmap; }
	D2D1_SIZE_F GetSize() const { return m_bitmapSize; }
};

