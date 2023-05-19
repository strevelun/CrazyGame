#pragma once

#include <d2d1.h>
#include <unordered_map>
#include <map>
#include <string>
#include "Setting.h"

class CBitmap;
class CAnimator;
class CAnimationClip;

class CResourceManager
{
private:
	static CResourceManager* m_inst;

	std::unordered_map<PCWSTR, CBitmap*> m_mapBitmap;
	std::map<std::wstring, std::vector<_tSprite*>> m_mapSprite; // TODO delete
	std::vector<CBitmap*> m_vecBitmap;
	std::map<std::wstring, CAnimationClip*> m_mapAnimClip;

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

	void LoadSprites(std::wstring folderName);
	void LoadAnimFiles(std::wstring folderName);
	tMapData LoadMapData(PCWSTR _wcFileName);

	// m_mapBitmap에서 찾고 있으면 리턴, 없으면 LoadImageFromFile호출 후 insert 후 리턴
	CBitmap* GetBitmap(PCWSTR _wcFileName);
	_tSprite* GetSprite(std::wstring key, int idx);
	CBitmap* GetIdxBitmap(int _idx) const { return m_vecBitmap.at(_idx); }

	CAnimationClip* GetAnimationClip(const std::wstring& _str);

	void DeleteAllResource();
};

