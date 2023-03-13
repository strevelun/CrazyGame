#include "CApp.h"
#include "CCore.h"
#include "../CrazyGame/CrazyGame/CSceneManager.h"
#include "../CrazyGame/CrazyGame/CLobbyScene.h"
#include "../CrazyGame/CrazyGame/CInputManager.h"
#include "../CrazyGame/CrazyGame/CMouse.h"

#include <windowsx.h>

CApp* CApp::m_inst = nullptr;

HRESULT CApp::Init(HINSTANCE hInstance, int nCmdShow, int _width, int _height)
{
	CCore::GetInst()->Init();


	m_hInst = hInstance;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = m_hInst;
	wcex.hIcon = LoadIcon(m_hInst, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"game";
	wcex.hIconSm = LoadIcon(m_hInst, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	RECT rc = { 0, 0, _width, _height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	m_hWnd = CreateWindow(L"game", L"CrazyGame", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInst,
		this);
	if (!m_hWnd) return S_FALSE;


	m_pRenderTarget = CCore::GetInst()->CreateRenderTarget(m_hWnd);
	CSceneManager::GetInst()->CreateScene<CLobbyScene>();

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return S_OK;
}

int CApp::Run()
{
	MSG msg = { 0 };

	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			Input();
			Update();
			Render();
		}
	}

	CCore::GetInst()->CleanupDevice();
	CCore::DeleteInst();

	return (int)msg.wParam;
}


void CApp::Input()
{
	CInputManager::GetInst()->Input();
	CSceneManager::GetInst()->Input();
}

void CApp::Update()
{

}

void CApp::Render()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear();
	CSceneManager::GetInst()->Render(m_pRenderTarget);
	CInputManager::GetInst()->GetMouse()->Render(m_pRenderTarget);
	m_pRenderTarget->EndDraw();
}

LRESULT CApp::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	return 0;
}