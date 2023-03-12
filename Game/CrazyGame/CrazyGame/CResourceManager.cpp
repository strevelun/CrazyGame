#include "CResourceManager.h"
#include "../../D2DCore/CCore.h"
#include "CBitmap.h"
#include "../../D2DCore/CApp.h"

#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

CResourceManager* CResourceManager::m_inst = nullptr;

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
}

ID2D1Bitmap* CResourceManager::LoadImageFromFile(PCWSTR _wcFileName, ID2D1HwndRenderTarget* _pRenderTarget)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	const wchar_t* str = L"resource/";

	size_t concatenatedStringLength = wcslen(_wcFileName) + wcslen(str) + 1;
	wchar_t* concatenatedString = new wchar_t[concatenatedStringLength];

	wcscpy_s(concatenatedString, concatenatedStringLength, str);
	wcscat_s(concatenatedString, concatenatedStringLength, _wcFileName);

	IWICImagingFactory* pWICImagingFactory = CCore::GetInst()->GetWICImagingFactory();

	hr = pWICImagingFactory->CreateDecoderFromFilename(concatenatedString, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);
	if (FAILED(hr)) return nullptr;
	delete[] concatenatedString;

	IWICBitmapFrameDecode* pFrame = nullptr;
	hr = pDecoder->GetFrame(0, &pFrame);
	if (FAILED(hr)) return nullptr;

	IWICFormatConverter* pConverter = nullptr;
	hr = pWICImagingFactory->CreateFormatConverter(&pConverter);
	if (FAILED(hr)) return nullptr;

	hr = pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return nullptr;

	ID2D1Bitmap* pBitmap;
	_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pBitmap);

	if (pConverter) { pConverter->Release(); pConverter = nullptr; }
	if (pFrame) { pFrame->Release(); pFrame = nullptr; }
	if (pDecoder) { pDecoder->Release(); pDecoder = nullptr; }

	return pBitmap;
}

CBitmap* CResourceManager::Load(PCWSTR _wcFileName)
{
	std::unordered_map<PCWSTR, CBitmap*>::iterator iter = m_mapBitmap.find(_wcFileName);
	ID2D1Bitmap* image = nullptr;
	CBitmap* bitmap;

	if (iter == m_mapBitmap.end())
	{
		ID2D1HwndRenderTarget* pRenderTarget = CApp::GetInst()->GetRenderTarget();
		image = LoadImageFromFile(_wcFileName, pRenderTarget);
		if (image == nullptr) return nullptr;
		bitmap = new CBitmap();
		bitmap->SetBitmap(image);
		m_mapBitmap.insert(std::make_pair(_wcFileName, bitmap));
	}
	else
		bitmap = iter->second;
	
	return bitmap;
}
