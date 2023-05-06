#pragma once

#include <windows.h>
#include <d2d1.h>

#define MAX_LOADSTRING 100
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

class CApp
{
private:
	static CApp* m_inst;

	WCHAR szTitle[MAX_LOADSTRING] = {};
	WCHAR szWindowClass[MAX_LOADSTRING] = {};

	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
	ID2D1BitmapRenderTarget* m_pBitmapRenderTarget = nullptr;

private:
	CApp() { }
	~CApp() {}


public:
	static CApp* GetInst()
	{
		if (m_inst == nullptr)  m_inst = new CApp();
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst)
		{
			delete m_inst;
			m_inst = nullptr;
		}
	}

	void Input();
	void Update();
	void Render();

	ID2D1HwndRenderTarget* GetRenderTarget() const { return m_pRenderTarget; }
	HWND GetHwnd() const { return m_hWnd; }
	HRESULT Init(HINSTANCE hInstance, int nCmdShow, int _width, int _height);
	int Run();
	void ExitGame() { DestroyWindow(m_hWnd); }

	LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};