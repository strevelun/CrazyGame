#pragma once

#include <d2d1.h>
#include <unordered_map>
#include <map>
#include <string>
#include "Setting.h"

class CBitmap;
class CAnimation;
class CAnimationClip;

class CResourceManager
{
private:
	static CResourceManager* m_inst;

	std::unordered_map<PCWSTR, CBitmap*> m_mapBitmap;
	std::map<std::string, std::vector<_tSprite*>> m_mapImage; // TODO delete
	std::vector<CBitmap*> m_vecBitmap;
	std::map<std::string, CAnimationClip*> m_mapAnimClip;

	int m_bitmapIdx = 0;

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

	void LoadFiles(std::wstring folderName);
	void LoadAnimFiles(std::wstring folderName);
	CBitmap* Load(PCWSTR _wcFileName);
	tMapData LoadMapData(PCWSTR _wcFileName);

	_tSprite* GetImage(std::string key, int idx) { return m_mapImage.at(key).at(idx); }
	CBitmap* GetIdxBitmap(int _idx) const { return m_vecBitmap.at(_idx); }

	void SetIdxBitmap(CBitmap* _bitmap) { m_vecBitmap.push_back(_bitmap); }
	CAnimationClip* GetAnimationClip(const std::string& _str) { return m_mapAnimClip.at(_str); }
};

