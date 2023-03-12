#pragma once

#include <d2d1.h>
#include <unordered_map>
#include <string>

class CBitmap;

class CResourceManager
{
private:
	static CResourceManager* m_inst;

	std::unordered_map<PCWSTR, CBitmap*> m_mapBitmap;

	CResourceManager();
	~CResourceManager();

	ID2D1Bitmap* LoadImageFromFile(PCWSTR _wcFileName, ID2D1HwndRenderTarget* _pRenderTarget);

public:
	static CResourceManager* GetInst()
	{
		if (m_inst == nullptr) m_inst = new CResourceManager;
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst != nullptr) { delete m_inst;	m_inst = nullptr; }
	}

	CBitmap* Load(PCWSTR _wcFileName);
};

