#include "CSceneManager.h"
#include "CScene.h"

CSceneManager* CSceneManager::m_inst = nullptr;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Input()
{
	m_pScene->Input();
}

void CSceneManager::Update()
{

}

void CSceneManager::Render(ID2D1RenderTarget* _pRenderTarget)
{
	m_pScene->Render(_pRenderTarget);
}

bool CSceneManager::NextScene(void)
{
	if (m_pNextScene == nullptr) return false;

	if (m_pScene)
	{
		m_pScene->Clean();
		delete m_pScene;
		m_pScene = nullptr;
	}

	m_pScene = m_pNextScene;
	m_pNextScene = nullptr;

	return true;
}
