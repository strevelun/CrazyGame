#include "CSceneManager.h"
#include "CScene.h"

CSceneManager* CSceneManager::m_inst = nullptr;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::AddScene(std::string _strSceneName, CScene* _scene)
{
	m_mapScene.insert(std::make_pair(_strSceneName, _scene));
}

CScene* CSceneManager::GetScene(const std::string& _strKey)
{
	auto scene = m_mapScene.find(_strKey);
	if (scene == m_mapScene.end()) return nullptr;

	return scene->second;
}

void CSceneManager::Input()
{
	m_pScene->Input();
}

void CSceneManager::Update()
{
	m_pScene->Update();

}

void CSceneManager::Render(ID2D1RenderTarget* _pRenderTarget)
{
	m_pScene->Render(_pRenderTarget);
}

bool CSceneManager::CheckNextScene(void)
{
	if (m_pNextScene == nullptr) return false;

	if (m_pScene != m_pNextScene)
	{
		if (m_pScene)
		{
			m_pScene->Clean();
		}
		m_pScene = m_pNextScene;
		m_pScene->Init();
	}

	m_pNextScene = nullptr;

	return true;
}

bool CSceneManager::ChangeScene(const std::string& _strKey)
{
	auto scene = m_mapScene.find(_strKey);
	if (scene == m_mapScene.end()) return false;

	CScene* pScene = scene->second;
	m_pNextScene = pScene;

	return true;
}
