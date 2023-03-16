#include "CResourceManager.h"
#include "../../D2DCore/CCore.h"
#include "CBitmap.h"
#include "../../D2DCore/CApp.h"
#include "Setting.h"
#include "CAnimation.h"

#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

CResourceManager* CResourceManager::m_inst = nullptr;

CResourceManager::CResourceManager()
{
}

CResourceManager::~CResourceManager()
{
	// delete
}

ID2D1Bitmap* CResourceManager::LoadImageFromFile(PCWSTR _wcFileName, ID2D1HwndRenderTarget* _pRenderTarget)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = nullptr;

	const wchar_t* str = L"resource/image/";

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

void CResourceManager::LoadFiles(std::wstring folderName)
{

	ID2D1HwndRenderTarget* pRenderTarget = CApp::GetInst()->GetRenderTarget();

	std::wstring searchPath = folderName + L"*.spr";

	int size = WideCharToMultiByte(CP_UTF8, 0, searchPath.c_str(), -1, NULL, 0, NULL, NULL);
	char* str = new char[size];
	WideCharToMultiByte(CP_UTF8, 0, searchPath.c_str(), -1, str, size, NULL, NULL);
	std::string result(str);
	delete[] str;
	std::string fileName = result;

	D2D1_BITMAP_PROPERTIES bpp;
	bpp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bpp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	bpp.dpiX = (FLOAT)0;
	bpp.dpiY = (FLOAT)0;

	int clipSize = 0;

	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile((LPCWSTR)searchPath.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				int size = WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, NULL, 0, NULL, NULL);

				std::wstring fileName(fd.cFileName);
				std::wstring filePath = folderName + fileName;

				FILE* pFile = nullptr;
				errno_t errNum = _wfopen_s(&pFile, filePath.c_str(), L"rb");
				
				if (pFile == nullptr || errNum != 0)
					return;

				fread(&clipSize, sizeof(int), 1, pFile);
				D2D1_SIZE_F bitmapSize;
				fread(&bitmapSize, sizeof(D2D1_SIZE_F), 1, pFile);

				CBitmap* bitmap = new CBitmap();

				bitmap->SetSize(bitmapSize);
				DWORD* pixel = new DWORD[sizeof(DWORD) * bitmapSize.width * bitmapSize.height];
				fread(&pixel[0], sizeof(DWORD) * bitmapSize.width, bitmapSize.height, pFile);
				ID2D1Bitmap* d2dBitmap;
				pRenderTarget->CreateBitmap(D2D1::SizeU(bitmapSize.width, bitmapSize.height), pixel, bitmapSize.width * 4, &bpp, &d2dBitmap);

				delete[] pixel;

				bitmap->SetBitmap(d2dBitmap);

				tSpriteData* arr = new tSpriteData[clipSize];

				fread(arr, sizeof(tSpriteData), clipSize, pFile);

				for (int i = 0; i < clipSize; i++)
				{
					_tSprite* sprite = new _tSprite(arr[i]);

					switch (sprite->type)
					{
					case eType::Tile:
						m_mapImage["Tile"].push_back(sprite);
						break;
					case eType::Block:
						m_mapImage["Block"].push_back(sprite);
						break;
					case eType::Character:
						m_mapImage["Character"].push_back(sprite);
						break;
					}
					sprite->idx = m_bitmapIdx;
				}

				SetIdxBitmap(bitmap);
				delete[] arr;
				m_bitmapIdx++;
				fclose(pFile);
			}
		} while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
	}
	else {
		//cout << "Unable to open the folder." << endl;
		return;
	}
}

void CResourceManager::LoadAnimFiles(std::wstring folderName)
{
	ID2D1HwndRenderTarget* pRenderTarget = CApp::GetInst()->GetRenderTarget();

	std::wstring searchPath = folderName + L"*.anim";

	int size = WideCharToMultiByte(CP_UTF8, 0, searchPath.c_str(), -1, NULL, 0, NULL, NULL);
	char* str = new char[size];
	WideCharToMultiByte(CP_UTF8, 0, searchPath.c_str(), -1, str, size, NULL, NULL);
	std::string result(str);
	delete[] str;
	std::string fileName = result;

	D2D1_BITMAP_PROPERTIES bpp;
	bpp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bpp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	bpp.dpiX = (FLOAT)0;
	bpp.dpiY = (FLOAT)0;

	int clipSize = 0;

	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile((LPCWSTR)searchPath.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				int size = WideCharToMultiByte(CP_UTF8, 0, fd.cFileName, -1, NULL, 0, NULL, NULL);

				std::wstring fileName(fd.cFileName);
				std::wstring filePath = folderName + fileName;

				FILE* pFile = nullptr;
				errno_t errNum = _wfopen_s(&pFile, filePath.c_str(), L"rb");

				if (pFile == nullptr || errNum != 0)
					return;

				TCHAR animName[100];
				fread(&animName, 100, 1, pFile);
				fread(&clipSize, sizeof(int), 1, pFile);
				D2D1_SIZE_F bitmapSize;
				fread(&bitmapSize, sizeof(D2D1_SIZE_F), 1, pFile);

				CBitmap* bitmap = new CBitmap();

				bitmap->SetSize(bitmapSize);
				DWORD* pixel = new DWORD[sizeof(DWORD) * bitmapSize.width * bitmapSize.height];
				fread(&pixel[0], sizeof(DWORD) * bitmapSize.width, bitmapSize.height, pFile);
				ID2D1Bitmap* d2dBitmap;
				pRenderTarget->CreateBitmap(D2D1::SizeU(bitmapSize.width, bitmapSize.height), pixel, bitmapSize.width * 4, &bpp, &d2dBitmap);

				delete[] pixel;

				bitmap->SetBitmap(d2dBitmap);

				tSpriteData* arr = new tSpriteData[clipSize];

				fread(arr, sizeof(tSpriteData), clipSize, pFile);

				CAnimation* anim = new CAnimation();

				for (int i = 0; i < clipSize; i++)
				{
					tAnimationClip* clip = new tAnimationClip(arr[i]);
					clip->idx = m_bitmapIdx;
					anim->AddClip(clip);
				}

				SetIdxBitmap(bitmap);
				m_bitmapIdx++;

				std::wstring wstrName(animName);
				std::string strName(wstrName.begin(), wstrName.end());
				m_mapAnim.insert(std::make_pair(strName, anim));

				delete[] arr;
				fclose(pFile);
			}
		} while (::FindNextFile(hFind, &fd));

		::FindClose(hFind);
	}
	else {
		//cout << "Unable to open the folder." << endl;
		return;
	}
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
	else // 인게임  ->  로비
		bitmap = iter->second;
	
	return bitmap;
}

tMapData CResourceManager::LoadMapData(PCWSTR _wcFileName)
{
	const wchar_t* str = L"resource/map/";

	size_t concatenatedStringLength = wcslen(_wcFileName) + wcslen(str) + 1;
	wchar_t* concatenatedString = new wchar_t[concatenatedStringLength];

	wcscpy_s(concatenatedString, concatenatedStringLength, str);
	wcscat_s(concatenatedString, concatenatedStringLength, _wcFileName);

	FILE* pFile = nullptr;
	errno_t errNum = _wfopen_s(&pFile, concatenatedString, L"rb");
	delete[] concatenatedString;

	if (pFile == nullptr || errNum != 0)
	{
		MessageBox(NULL, L"맵 파일이 존재하지 않습니다.", L"오류", MB_OK);
		CApp::GetInst()->ExitGame();
	}

	int gridX, gridY;
	tMapData mapData;

	fread(&gridX, sizeof(int), 1, pFile);
	fread(&gridY, sizeof(int), 1, pFile);

	mapData.gridX = gridX;
	mapData.gridY = gridY;

	eMenuEvent event;

	for (int i = 0; i < gridY; i++)
	{
		for (int j = 0; j < gridX; j++)
		{
			fread(&event, sizeof(eMenuEvent), 1, pFile);
			mapData.vecEventData.push_back(event);
		}
	}

	int x, y;
	int idx;
	eType type;

	while (fread(&x, sizeof(int), 1, pFile) == 1 &&
		fread(&y, sizeof(int), 1, pFile) == 1 &&
		fread(&type, sizeof(eType), 1, pFile) == 1 &&
		fread(&idx, sizeof(int), 1, pFile) == 1)
	{
		tBlockData blockData = { x, y, idx, type };
		mapData.vecBlockData.push_back(blockData);
	}

	fclose(pFile);

	return mapData;
}