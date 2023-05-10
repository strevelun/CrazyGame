#include "CSceneManager.h"
#include "CScene.h"
#include "CResourceManager.h"
#include "../../D2DCore/CApp.h"

#include <unordered_map>

CSceneManager* CSceneManager::m_inst = nullptr;

CSceneManager::CSceneManager()
{
	tMapData mapData = CResourceManager::GetInst()->LoadMapData(L"village.map");
	m_mapData.insert(std::make_pair("village.map", mapData));

	mapData = CResourceManager::GetInst()->LoadMapData(L"pirate.map");
	m_mapData.insert(std::make_pair("pirate.map", mapData));

	mapData = CResourceManager::GetInst()->LoadMapData(L"test.map");
	m_mapData.insert(std::make_pair("test.map", mapData));

}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::AddScene(std::string _strSceneName, CScene* _scene)
{
	_scene->SetName(_strSceneName);
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

void CSceneManager::Render(ID2D1BitmapRenderTarget* _pRenderTarget)
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
			m_pScene->Cleanup();
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

tMapData& CSceneManager::FindMapData(const std::string& _strName)
{
	std::unordered_map<std::string, tMapData>::iterator iter = m_mapData.find(_strName);
	if (iter == m_mapData.end())
	{
		MessageBox(NULL, L"m_mapData에 해당 키 값의 데이터가 없습니다.", L"오류", MB_OK);
		CApp::GetInst()->ExitGame();
	}
	return iter->second;
}