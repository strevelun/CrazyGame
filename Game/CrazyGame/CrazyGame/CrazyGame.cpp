#include "../../D2DCore/CApp.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(CApp::GetInst()->Init(hInstance, nCmdShow, 1024, 768)))
		return 0;

	int ret = CApp::GetInst()->Run();
	CApp::DestroyInst();
	return ret;
}

