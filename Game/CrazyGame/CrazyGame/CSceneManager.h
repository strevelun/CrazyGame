#pragma once

#include <d2d1.h>

class CScene;

class CSceneManager
{
private:
	CScene* m_pScene;
	CScene* m_pNextScene ;

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
	T* CreateScene() { return new T(); }

	void SetNextScene(CScene* _scene);
	void SetScene(CScene* _scene) { m_pScene = _scene; }

	void Input();
	void Update();
	void Render(ID2D1RenderTarget* _pRenderTarget);

	bool NextScene(void);
};

