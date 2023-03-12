#pragma once

#include <d2d1.h>

class CBitmap
{
	ID2D1Bitmap* m_pD2dBitmap = nullptr;

public:
	void SetBitmap(ID2D1Bitmap* _bitmap);

	ID2D1Bitmap* GetBitmap() const { return m_pD2dBitmap; }
};

