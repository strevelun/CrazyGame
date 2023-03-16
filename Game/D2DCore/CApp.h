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

private:
	CApp() { }
	~CApp() {}

	static LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static CApp* GetInst()
	{
		if (m_inst == nullptr)  m_inst = new CApp();
		return m_inst;
	}

	void Input();
	void Update();
	void Render();

	ID2D1HwndRenderTarget* GetRenderTarget() const { return m_pRenderTarget; }
	HWND GetHwnd() const { return m_hWnd; }
	HRESULT Init(HINSTANCE hInstance, int nCmdShow, int _width, int _height);
	int Run();
	void ExitGame() { DestroyWindow(m_hWnd); }
	void DrawIntToText(int _value);
};