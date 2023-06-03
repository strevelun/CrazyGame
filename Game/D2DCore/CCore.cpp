#include "CCore.h"
#include "CApp.h"

CCore* CCore::m_inst = nullptr;

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

CCore::CCore()
{
}

CCore::~CCore()
{

}

HRESULT CCore::InitDevice()
{
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (FAILED(hr)) return hr;

	CoInitialize(nullptr);
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory));
	if (FAILED(hr)) return hr;

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_writeFactory)
	);

	m_writeFactory->CreateTextFormat(
		L"Arial", // font family name
		NULL, // font collection
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		24.0f, // font size
		L"en-us", // locale name
		&m_textFormat
	);

	return hr;
}

void CCore::CleanupDevice()
{
	if (m_pD2DFactory) m_pD2DFactory->Release();
	CoUninitialize();
}

bool CCore::Init()
{
	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return false;
	}
}

ID2D1HwndRenderTarget* CCore::CreateRenderTarget(HWND _hWnd)
{
	HRESULT hr = S_OK;
	ID2D1HwndRenderTarget* renderTarget = nullptr;

	RECT	rc;
	GetClientRect(_hWnd, &rc);

	hr = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE),
		D2D1::HwndRenderTargetProperties(_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
		&renderTarget);
	if (FAILED(hr)) return nullptr;

	return renderTarget;
}
