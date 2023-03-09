#include "CApp.h"
#include "CCore.h"

#include <windowsx.h>

CApp* CApp::m_inst = nullptr;

HRESULT CApp::Init(HINSTANCE hInstance, int nCmdShow)
{
	CCore::GetInst()->Init();



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

	}

	CCore::GetInst()->CleanupDevice();
	CCore::DeleteInst();

	return (int)msg.wParam;
}

