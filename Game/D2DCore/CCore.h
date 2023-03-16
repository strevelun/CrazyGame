#pragma once

#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>

#pragma comment(lib, "dwrite.lib")

class CCore
{
private:
	static CCore* m_inst;

	CCore();
	~CCore();

	ID2D1Factory* m_pD2DFactory = nullptr;
	IWICImagingFactory* m_pWICFactory = nullptr;
	IDWriteFactory* m_writeFactory = nullptr;
	IDWriteTextFormat * m_textFormat = nullptr;
	ID2D1SolidColorBrush* m_brush = nullptr;

private:
	HRESULT InitDevice();

public:

	static CCore* GetInst()
	{
		if (m_inst == nullptr)
			m_inst = new CCore();
		return m_inst;
	}

	static void DeleteInst()
	{
		if (m_inst != nullptr)
		{
			delete m_inst;
			m_inst = nullptr;
		}
	}

	bool Init();

	ID2D1HwndRenderTarget* CreateRenderTarget(HWND _hWnd);

	IWICImagingFactory* GetWICImagingFactory() const { return m_pWICFactory; }
	IDWriteTextFormat* GetTextFormat() const { return m_textFormat; }
	ID2D1SolidColorBrush* GetBrush() const { return m_brush; }

	void SetBrush(ID2D1SolidColorBrush* _brush) { m_brush = _brush; }

	void CleanupDevice();
};