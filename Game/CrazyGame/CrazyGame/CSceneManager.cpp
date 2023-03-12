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
}

void CSceneManager::Update()
{
}

void CSceneManager::Render(ID2D1RenderTarget* _pRenderTarget)
{
	m_pScene->Render(_pRenderTarget);
}
