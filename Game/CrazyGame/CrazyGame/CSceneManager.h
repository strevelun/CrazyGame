#pragma once

#include <d2d1.h>

class CScene;

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pPrevScene;

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

	// ¾À ¸¸µé±â
	template <typename T>
	T* CreateScene()
	{
		//if (m_pScene)
		//	delete m_pScene;

		T* scene = new T;

		m_pPrevScene = m_pScene;
		m_pScene = scene;

		return scene;
	}

	void Input();
	void Update();
	void Render(ID2D1RenderTarget* _pRenderTarget);
};

