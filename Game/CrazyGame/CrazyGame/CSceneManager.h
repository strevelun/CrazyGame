#pragma once

#include <d2d1.h>
#include <list>
#include <map>
#include <unordered_map>
#include <string>

#include "Setting.h"

class CScene;


// ¾À °ü¸®
class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene;
	std::map<std::wstring, CScene*> m_mapScene;

private:
	static CSceneManager* m_inst;

	CSceneManager();
	~CSceneManager();


public:
	static CSceneManager* GetInst()
	{
		if (m_inst == nullptr) m_inst = new CSceneManager;
		return m_inst;
	}

	static void DestroyInst()
	{
		if (m_inst != nullptr) { delete m_inst;	m_inst = nullptr; }
	}

	template <typename T>
	T* CreateScene() 
	{ 
		T* scene = new T();
		//m_pScene = scene;
		return scene; 
	}

	void AddScene(std::wstring _strSceneName, CScene* _scene);

	CScene* GetCurScene() const { return m_pScene; }
	CScene* GetScene(const std::wstring& _strKey);

	void Input();
	void Update();
	void Render(ID2D1BitmapRenderTarget* _pRenderTarget);

	bool CheckNextScene(void);

	bool ChangeScene(const std::wstring& _strKey);
};

