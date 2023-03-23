#include "CApp.h"
#include "CCore.h"
#include "../CrazyGame/CrazyGame/CSceneManager.h"
#include "../CrazyGame/CrazyGame/CLobbyScene.h"
#include "../CrazyGame/CrazyGame/CInGameScene.h"
#include "../CrazyGame/CrazyGame/CInputManager.h"
#include "../CrazyGame/CrazyGame/CMouse.h"
#include "../CrazyGame/CrazyGame/CResourceManager.h"
#include "../CrazyGame/CrazyGame/CTimer.h"

#include <windowsx.h>

CApp* CApp::m_inst = nullptr;
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

HRESULT CApp::Init(HINSTANCE hInstance, int nCmdShow, int _width, int _height)
{
	CCore::GetInst()->Init();



	m_hInst = hInstance;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
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

	ID2D1SolidColorBrush* brush = nullptr;
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&brush
	);

	CCore::GetInst()->SetBrush(brush);

	CSceneManager::GetInst()->AddScene("LobbyScene", CSceneManager::GetInst()->CreateScene<CLobbyScene>());
	CSceneManager::GetInst()->AddScene("InGameScene", CSceneManager::GetInst()->CreateScene<CInGameScene>());
	CSceneManager::GetInst()->ChangeScene("LobbyScene");

	CResourceManager::GetInst()->LoadFiles(L"resource/sprite/");
	CResourceManager::GetInst()->LoadAnimFiles(L"resource/anim/");
	//CTimer::GetInst()->SetFrameLimit(10);

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
			if (CTimer::GetInst()->Update())
			{
				CSceneManager::GetInst()->CheckNextScene();
				Input();
				Update();
				Render();
			}
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
	CSceneManager::GetInst()->Update();
}

void CApp::Render()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear();
	CSceneManager::GetInst()->Render(m_pRenderTarget);
	CInputManager::GetInst()->GetMouse()->Render(m_pRenderTarget);
	m_pRenderTarget->EndDraw();
}

LRESULT CALLBACK CApp::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	CApp* pApp = nullptr;

	if (_msg == WM_NCCREATE)
	{
		LPCREATESTRUCT pCS = (LPCREATESTRUCT)_lParam;
		SetLastError(0);
		pApp = (CApp*)pCS->lpCreateParams;
		if (!SetWindowLongPtr(_hWnd, GWLP_USERDATA, (LONG_PTR)pApp))
		{
			if (GetLastError() != 0) return E_FAIL;
		}
	}
	else
	{
		pApp = reinterpret_cast<CApp*>(GetWindowLongPtr(_hWnd, GWLP_USERDATA));
	}

	if (pApp)
	{
		return pApp->Proc(_hWnd, _msg, _wParam, _lParam);
	}

	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}