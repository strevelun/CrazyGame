#include "CBitmap.h"


void CBitmap::SetBitmap(ID2D1Bitmap* _bitmap)
{
	if (m_pD2dBitmap) m_pD2dBitmap->Release(); 
	m_pD2dBitmap = _bitmap;
}
